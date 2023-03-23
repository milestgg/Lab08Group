#include <QString>
#include <QFile>
#ifndef PASSWORDVALIDATOR_H
#define PASSWORDVALIDATOR_H


class PasswordValidator
{
public:
    PasswordValidator();

       bool validatePassword(QString);
};

#endif // PASSWORDVALIDATOR_H
