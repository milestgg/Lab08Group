#include "selogger.h"

#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QTextStream>
#include <QIODevice>


SELogger::SELogger() // Creates log in current directory
{
    QFile file("log.txt");
    QDir current;
    logFilepath = current.absoluteFilePath("log.txt");
    file.open(QIODevice::WriteOnly);
    file.write("Log created by default constructor\n\n");
}

SELogger::SELogger(QString fp) // Creates log in specified directory
{
    QDir directory(fp);
    QString absPath = directory.absoluteFilePath("log.txt");
    QFile file(absPath);
    logFilepath = absPath;
    qDebug() << "Absolute path to (overloaded) log.txt:";
    qDebug() << absPath;
    qDebug() << "\n";
    file.open(QIODevice::WriteOnly);
    file.write("Log created by overloaded constructor\n\n");
}

QString SELogger::formatTime(QString format)
{
    QDateTime now = QDateTime::currentDateTime();
    QString formattedTime = now.toString(format);
    return formattedTime;
}

int SELogger::logError(QString message)
{
    QFile file(logFilepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QTextStream out(&file);
        out << formatTime("yyyyMMdd_HH:MM:ss") << ": " << message << "\n";
        return 0;
    } else {
        qDebug() << "logError() is busted";
        return -1;
    }
}

int SELogger::logUserMsg(QString user, QString message)
{
    QFile file(logFilepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QTextStream out(&file);
        out << message << " occurred for " << user << " at " << formatTime("yyyyMMdd_HH:MM:ss") << "\n";
        return 0;
    } else {
        qDebug() << "logUserMsg() is busted";
        return -1;
    }
}
