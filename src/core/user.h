#ifndef USER_H
#define USER_H

#include <QString>
#include <QCryptographicHash>

class User
{
private:
    QString userName;
    QString privateKeyPath;

public:
    User(QString name, QString privateKeyPath);
    ~User();
    QString getUserName();
    QString getPrivateKeyPath();
};

#endif // USER_H
