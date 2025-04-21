#ifndef SSHCLIENT_H
#define SSHCLIENT_H

#include "qobject.h"
#include "user.h"

#include <QString>
#include <QProcess>
#include <QObject>

struct SshClientError {};

class SshClient : public QObject
{
private:
    QString host;
    User user;
    QProcess * session;
    bool isConnected;

public:
    /**
     * @brief SshClient
     * @param host ip address of the server
     * @param user used to authentificate
     */
    SshClient(const QString& host, const User& user);
    ~SshClient();

    /**
     * @brief Start session with ssh server
     */
    void connect();
    /**
     * @brief Excute ssh command on server
     * @param The command to be executed
     * @return Response of the server
     */
    QString executeCommand(const QString& command);
    QStringList executeCommands(const QStringList & commands);
    /**
     * @brief End session with ssh server
     */
    void disconnect();
};

#endif // SSHCLIENT_H
