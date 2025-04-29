#include "commandspipeline.h"
#include "qthread.h"
#include <QDebug>
#include <QCoreApplication>

CommandsPipeline::CommandsPipeline(const Computer & computer, QObject *parent)
    : QObject(parent)
    , client(SshClient(computer, this))
    , worker(new QThread)
{
    this->client.getSession()->moveToThread(this->worker);
    this->worker->start();
}

CommandsPipeline::~CommandsPipeline()
{
    this->client.disconnect();
    this->worker->quit();
    this->worker->wait();
    this->client.getSession()->deleteLater();
    this->worker->deleteLater();
}

void CommandsPipeline::run(const QStringList & commands)
{
    QMetaObject::invokeMethod(this->client.getSession(), [=]() {
        this->client.connect();
        this->client.executeCommands(commands);
        this->client.disconnect();
    },Qt::QueuedConnection);
}
void CommandsPipeline::run(const QString & command)
{
    QMetaObject::invokeMethod(this->client.getSession(), [=]() {
        this->client.connect();
        this->client.executeCommand(command);
        this->client.disconnect();
    },Qt::QueuedConnection);
}

const SshClient & CommandsPipeline::getClient()
{
    return this->client;
}
