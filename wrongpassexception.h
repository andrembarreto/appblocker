#ifndef WRONGPASSEXCEPTION_H
#define WRONGPASSEXCEPTION_H

#include <QException>

class WrongPassException : public QException
{
public:
    void raise() const override { throw *this; }
    WrongPassException *clone() const override { return new WrongPassException(*this); }
};

#endif // WRONGPASSEXCEPTION_H
