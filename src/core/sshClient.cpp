#include <core/sshClient.h>
#include <core/exception.h>
#include <QDebug>

SshClient::SshClient(const Computer & computer, QObject * parent)
    : QObject(parent)
    , computer(computer)
    , session(new QProcess)
    , isConnected(false)
{
    QProcess::connect(this->session, &QProcess::errorOccurred, this, &SshClient::handleConnectionError);
}

SshClient::~SshClient() {}

void SshClient::connect()
{
    QStringList args;
    args << "-tt"
         << "-i" << this->computer.getUser().getPrivateKeyPath() //private key
         << "-p" << QString::number(this->computer.getSshPort()) //server ssh port
         << this->computer.getUser().getUserName() + "@" + this->computer.getIpAddress(); //username@ip

    session->start("ssh", args);

    if (!session->waitForStarted(3000))
    {
        this->handleConnectionError(this->session->error());
        this->isConnected = false;
        return;
    }

    if (!this->session->waitForReadyRead(3000))
    {
        this->handleConnectionError(this->session->error());
        this->isConnected = false;
        return;
    }

    this->isConnected = true;
    emit this->connectionOpen();
}

void SshClient::disconnect()
{
    if (isConnected) {
            session->kill();
            session->waitForFinished(3000);
            isConnected = false;
            emit connectionClosed();
    }
}

void SshClient::executeCommand(const QString & command)
{
    if (!this->isConnected) {
        emit this->commandError("SSH not connected.");
        return;
    }

        session->write((command + "\n").toUtf8());

        if (!session->waitForBytesWritten(3000)) {
            emit this->commandError("Timeout when writing command.");
            return;
        }

        if (!session->waitForReadyRead(5000)) {
            emit this->commandError("Timeout waiting for command output.");
            return;
        }

        QString output = QString::fromUtf8(session->readAllStandardOutput());
        QString error = QString::fromUtf8(session->readAllStandardError());

        if (!error.isEmpty()) {
            emit this->commandError(error.trimmed());
        } else {
            emit this->commandResult(output.trimmed());
        }
        emit this->commandExecuted();
}

void SshClient::executeCommands(const QStringList & commands)
{
    if (!this->isConnected) {
        emit this->commandError("SSH not connected.");
        return;
    }

        for(const QString & command : commands)
        {
            session->write((command + "\n").toUtf8());
            if (!session->waitForBytesWritten(3000)) {
                emit this->commandError("Timeout when writing command.");
                return;
            }

            if (!session->waitForReadyRead(5000)) {
                emit this->commandError("Timeout waiting for command output.");
                return;
            }

            QString output = QString::fromUtf8(session->readAllStandardOutput());
            QString error = QString::fromUtf8(session->readAllStandardError());

            if (!error.isEmpty()) {
                emit this->commandError(error.trimmed());
            } else {
                emit this->commandResult(output.trimmed());
            }
        }
        emit this->commandExecuted();
}

QProcess * SshClient::getSession() const
{
    return session;
}

void SshClient::handleConnectionError(QProcess::ProcessError error)
{
    QString errorMessage;

    switch (error) {
    case QProcess::FailedToStart:
        errorMessage = "SSH process failed to start. Check if SSH is installed and accessible.";
        break;
    case QProcess::Crashed:
        errorMessage = "SSH process crashed unexpectedly.";
        break;
    case QProcess::Timedout:
        errorMessage = "SSH operation timed out.";
        break;
    case QProcess::WriteError:
        errorMessage = "SSH process write error (unable to send data).";
        break;
    case QProcess::ReadError:
        errorMessage = "SSH process read error (unable to receive data).";
        break;
    case QProcess::UnknownError:
    default:
        errorMessage = "An unknown SSH process error occurred.";
        break;
    }

    qWarning() << "[SSHClient] Process error : " << error << " : " << errorMessage;

    emit this->connectionFailed(errorMessage);

    this->disconnect();
}
