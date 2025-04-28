#include "commandspipeline.h"
#include <QDebug>

CommandsPipeline::CommandsPipeline(const Computer & computer, QObject *parent)
    : QObject(parent)
    , client(SshClient(computer, this)) {}

void CommandsPipeline::run(const QStringList & commands)
{
    QMetaObject::Connection executed =
        QProcess::connect(&(this->client), &SshClient::commandExecuted, this, [=]{
            this->client.disconnect();
        });
    QMetaObject::Connection connected =
        QProcess::connect(&(this->client), &SshClient::connectionOpen, this, [=]{
            this->client.executeCommands(commands);
        });
    QMetaObject::Connection failedToConnect;
    failedToConnect = QProcess::connect(&(this->client), &SshClient::connectionFailed, this, [=](const QString &) {
        qDebug() << "COUCOU";
        QProcess::disconnect(executed);
        QProcess::disconnect(connected);
        QProcess::disconnect(failedToConnect);
    });
    this->client.connect();
}
void CommandsPipeline::run(const QString & command)
{
    QMetaObject::Connection executed;
    executed = QProcess::connect(&(this->client), &SshClient::commandExecuted,
                                 this, [=]() {
        QProcess::disconnect(executed);
        this->client.disconnect();
    });
    QMetaObject::Connection connected;
    connected = QProcess::connect(&(this->client), &SshClient::connectionOpen,
                                  this, [=]() {
        QProcess::disconnect(connected);
        this->client.executeCommand(command);
    });
    QMetaObject::Connection failedToConnect;
    failedToConnect = QProcess::connect(&(this->client), &SshClient::connectionFailed,
                                        this, [=](const QString &) {
        QProcess::disconnect(executed);
        QProcess::disconnect(connected);
        QProcess::disconnect(failedToConnect);
    });
    this->client.connect();
}

const SshClient & CommandsPipeline::getClient()
{
    return this->client;
}
