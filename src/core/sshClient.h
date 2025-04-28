#ifndef SSHCLIENT_H
#define SSHCLIENT_H

#include <core/computer.h>

#include <QString>
#include <QProcess>
#include <QObject>

struct SshClientError {};

class SshClient : public QObject
{
    Q_OBJECT

private:
    const Computer & computer;
    QProcess * session;
    QThread * worker;
    bool isConnected;

    static QString processCommand(const QString & command);

private slots:
    void handleError(QProcess::ProcessError error);

signals:
    void connectionFailed(const QString & error);
    void connectionClosed();
    void connectionOpen();
    void commandExecuted();
    void commandResult(const QString & output);
    void commandError(const QString & error);

public:
    SshClient(const Computer & computer, QObject * parent = nullptr);
    ~SshClient();

    void connect();
    void executeCommand(const QString & command);
    void executeCommands(const QStringList & commands);
    void disconnect();

};

#endif // SSHCLIENT_H
