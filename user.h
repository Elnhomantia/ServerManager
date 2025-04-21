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
    User(QString name, QString privateKeyPath = "");
    ~User();
    QString getUserName();
    QString getPrivateKeyPath();

    void setPassphrase(const QString &newPassphrase);
};

#endif // USER_H
