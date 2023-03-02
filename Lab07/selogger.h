#ifndef SELOGGER_H
#define SELOGGER_H
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QDebug>


class SELogger
{
public:
    SELogger();
    SELogger(const QString& filepath);
    int logError(QString message);
    int logUserMsg(QString user, QString message);
private:
    QString ffilename;
    QTextStream ffile;
    int OpenFile();
    QString formatTime(QString format);
};

#endif // SELOGGER_H
