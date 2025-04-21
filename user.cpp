#include "user.h"

#include <QFile>
#include <QChar>
#include <QTextStream>

User::User(QString name, QString privateKeyPath):
    userName(name), privateKeyPath(privateKeyPath) {}
User::~User() {}

QString User::getUserName() { return this->userName; }
QString User::getPrivateKeyPath() { return this->privateKeyPath; }
