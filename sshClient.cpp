#include "sshClient.h"
#include "exception.h"
#include <QDebug>

SshClient::SshClient(const QString & host, const User & user)
    : host(host), user(user), session(nullptr), isConnected(false) {}

SshClient::~SshClient()
{
    this->disconnect();
}

void SshClient::connect()
{
    if(this->user.getPrivateKeyPath().isEmpty())
    {
        throw Exception<SshClientError>("Private key path needed");
    }
    QStringList args;
    args << "-tt" << "-i" << this->user.getPrivateKeyPath();
    args << this->user.getUserName() << "@" << this->host;
    this->session = new QProcess;
    this->session->start("ssh", args);

    if (!this->session->waitForStarted(5000))
    {
        qWarning() << this->session->errorString();
        throw Exception<SshClientError>("SSH process failed to start.");
    }
    this->isConnected = true;
}

QString SshClient::executeCommand(const QString & command)
{
    if(!this->isConnected)
    {
        throw Exception<SshClientError>("No ssh connection active");
    }
    this->session->write((command + "\n").toUtf8());
    this->session->waitForBytesWritten();
    this->session->waitForReadyRead();

    QString error = this->session->readAllStandardError();
    QString output = this->session->readAllStandardOutput();
    int exitCode = this->session->exitCode();

    if (!error.isEmpty() || exitCode != 0) {
        qWarning() << "SSH error output:" << stderr;
        Exception<SshClientError>(QString::number(exitCode) + " : " + error);
    }

    return output.trimmed();
}
QStringList SshClient::executeCommands(const QStringList & commands)
{
    if(this->isConnected == false)
    {
        throw Exception<SshClientError>("No ssh connection active");
    }
    QStringList results;
    for(const QString & command: commands)
    {
        try
        {
            results.append(this->executeCommand(command));
        } catch (const Exception<SshClientError> & e)
        {
            throw e;
        }

    }
    return results;
}

void SshClient::disconnect()
{
    if(this->isConnected)
    {
        this->session->write("exit\n");
        this->session->waitForFinished(3000);
        this->isConnected = false;
    }
}
