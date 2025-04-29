#ifndef COMMANDSPIPELINE_H
#define COMMANDSPIPELINE_H

#include <QObject>
#include <core/sshClient.h>
#include <QThread>

class CommandsPipeline : public QObject
{
    Q_OBJECT

private:
    SshClient client;
    QThread * worker;

public:
    CommandsPipeline(const Computer & com, QObject * parent = nullptr);
    ~CommandsPipeline();

    void add(const QString & command);

    void run(const QStringList & commands);
    void run(const QString & command);

    const SshClient & getClient();
};

#endif // COMMANDSPIPELINE_H
