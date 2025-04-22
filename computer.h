#ifndef COMPUTER_H
#define COMPUTER_H

#include <QString>

#include "user.h"

struct ComputerManagerError {};

class Computer
{
private:
    QString ipAddress;
    QString macAddress;
    QString name;
    User user;
    quint16 port;

public:
    Computer(User u, QString ip, QString mac, QString name, quint16 port);

    /**
     * @brief Use "wake on lan" feature to wake up the computer.
     * The macAddress and ip must be set.
     * @param port Configured port for wakeup.
     */
    void wakeup();
    /**
     * @brief Restart the computer.
     * The macAddress and ip must be set.
     */
    void reboot();
    /**
     * @brief shutdown Shutdown the computer.
     * The macAddress and ip must be set.
     */
    void shutdown();
    /**
     * @brief Verify if the computer is on
     * @return True if computer is on, false else
     */
    bool isAwake();
    void getStats();
    QString getName();
};

#endif // COMPUTER_H
