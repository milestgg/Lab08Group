#ifndef SELOGGER_H
#define SELOGGER_H

#include <QString>
#include <string>
#include <QFile>

class SELogger
{
public:
    SELogger();
    SELogger(QString filePath);

    int logError(QString message);
    int logUserMsg(QString user, QString message);

    QString logFilepath; // stores path to log

private:
    QString formatTime(QString format);

};
#endif // SELOGGER_H
