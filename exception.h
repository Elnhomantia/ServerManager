#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>

template<typename T>
class Exception: public QException
{
private:
    const QString _message;
    const T * _data;

public:
    explicit Exception(const QString& msg, const T * data = nullptr) : _message(msg), _data(data) {}

    void raise() const override { throw *this; }
    Exception *clone() const override { return new Exception(*this); }

    QString message() const { return _message; }
    T & data() { return _data; }
};

#endif // EXCEPTION_H
