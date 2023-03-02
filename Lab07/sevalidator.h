#include <QString>
#include <QFile>
#ifndef SEVALIDATOR_H
#define SEVALIDATOR_H

class SEValidator
{
public:
    SEValidator();

    bool validatePassword(QString);
};

#endif // SEVALIDATOR_H
