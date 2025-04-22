#include "computer.h"

#include <QUdpSocket>
#include <QDebug>
#include <QByteArray>

#include "sshClient.h"
#include "exception.h"

Computer::Computer(User u) : user(u) {}

void Computer::wakeup(quint16 port)
{
    QByteArray mac = QByteArray::fromHex(this->macAddress.remove(':').toLatin1());

    QByteArray packet;
    packet.fill(0xFF, 6);
    for (int i = 0; i < 16; ++i)
    {
        packet.append(mac);
    }

    QUdpSocket udpSocket;
    qint64 bytesSent = udpSocket.writeDatagram(packet, QHostAddress(this->ipAddress), port);

    if (bytesSent == -1) {
        qDebug() << "Could not send wakeup packet : " << udpSocket.errorString();
        throw Exception<ComputerManagerError>("Failed to launch wakeup command.");
    }
}
void Computer::reboot()
{
    QString command("sudo reboot");
    SshClient client(this->ipAddress, this->user);
    try {
    client.connect();
    client.executeCommand(command);
    client.disconnect();
    }
    catch (const Exception<SshClientError> & e) {
        client.disconnect();
        qDebug("%s", e.message().toStdString().c_str());
        throw Exception<ComputerManagerError>("Failed to launch reboot command.");
    }
}
void Computer::shutdown()
{
    QString command("sudo shutdown");
    try {
        SshClient client(this->ipAddress, this->user);
        client.connect();
        client.executeCommand(command);
        client.disconnect();
    }
    catch (const Exception<SshClientError> & e) {
        qDebug("%s", e.message().toStdString().c_str());
        throw Exception<ComputerManagerError>("Failed to launch shutdown command.");
    }
}
void Computer::getStats()
{
    QStringList commands;
    commands.append("top -bn1 | grep 'Cpu(s)'");
    commands.append("free -h");
    commands.append("sensors");
    commands.append("uptime");
    QStringList results;
    try {
        SshClient client(this->ipAddress, this->user);
        client.connect();
        results = client.executeCommands(commands);
    }
    catch (const Exception<SshClientError> & e) {
        qDebug("%s", e.message().toStdString().c_str());
        throw Exception<ComputerManagerError>("Failed to get computer stats.");
    }
}
