#ifndef COMPUTER_H
#define COMPUTER_H

#include <QString>
#include <QObject>

#include <core/user.h>

struct ComputerManagerError {};

class Computer : public QObject
{
    Q_OBJECT

private:
    QString ipAddress;
    QString macAddress;
    QString name;
    User user;
    quint16 wolPort;
    quint16 sshPort;

public:
    Computer(User u, QString ip, QString mac, QString name,
             quint16 wolPort, quint16 sshPort, QObject * parent = nullptr);

    /**
     * @brief Use "wake on lan" feature to wake up the computer.
     * The macAddress and ip must be set.
     * @param port Configured port for sendWolPacket.
     */
    void sendWolPacket();

    QString getName();

    quint16 getWolPort() const;
    User getUser() const;
    QString getMacAddress() const;
    QString getIpAddress() const;
    quint16 getSshPort() const;
};

#endif // COMPUTER_H
