#include <core/computer.h>

#include <QUdpSocket>
#include <QDebug>
#include <QByteArray>

#include <core/sshClient.h>
#include <core/exception.h>

quint16 Computer::getWolPort() const
{
    return wolPort;
}
User Computer::getUser() const
{
    return user;
}
QString Computer::getMacAddress() const
{
    return macAddress;
}
QString Computer::getIpAddress() const
{
    return ipAddress;
}
quint16 Computer::getSshPort() const
{
    return sshPort;
}
QString Computer::getName()
{
    return this->name;
}

Computer::Computer(User u, QString ip, QString mac, QString name,
                   quint16 wolPort, quint16 sshPort, QObject * parent)
    : QObject(parent)
    , ipAddress(ip)
    , macAddress(mac)
    , name(name)
    , user(u)
    , wolPort(wolPort)
    , sshPort(sshPort) {}

void Computer::sendWolPacket()
{
    QByteArray mac = QByteArray::fromHex(this->macAddress.remove(':').toLatin1());

    QByteArray packet;
    packet.fill(0xFF, 6);
    for (int i = 0; i < 16; ++i)
    {
        packet.append(mac);
    }

    QUdpSocket udpSocket;
    qint64 bytesSent = udpSocket.writeDatagram(packet, QHostAddress(this->ipAddress), this->wolPort);

    if (bytesSent == -1) {
        qDebug() << "Could not send wakeup packet : " << udpSocket.errorString();
        throw Exception<ComputerManagerError>("Failed to launch wakeup command.");
    }
}

