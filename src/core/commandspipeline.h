#ifndef COMMANDSPIPELINE_H
#define COMMANDSPIPELINE_H

#include <QObject>
#include <core/sshClient.h>

class CommandsPipeline : public QObject
{
    Q_OBJECT

private:
    SshClient client;

public:
    CommandsPipeline(const Computer & com, QObject * parent = nullptr);

    void add(const QString & command);

    void run(const QStringList & commands);
    void run(const QString & command);

    const SshClient & getClient();
};

#endif // COMMANDSPIPELINE_H
