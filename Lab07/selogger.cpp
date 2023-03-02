#include "selogger.h"
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QFile>

SELogger::SELogger()
{
    ffilename = "log.txt";
    OpenFile();



}
SELogger::SELogger(const QString& path){
    ffilename = path+ "/log.txt";
    OpenFile();
}
QString SELogger::formatTime(QString format){
    QDateTime currenttime = QDateTime::currentDateTime();
    return currenttime.toString(format);
}
int SELogger::logError(QString message){
    QFile file(ffilename);
    if(!file.open(QIODevice::Append | QIODevice::Text)){
        return -1;
    }
    QTextStream out(&file);
    out << Qt::endl << formatTime("yyyMMdd_hh:mm:ss") << ": (" <<message <<")"<< Qt::endl;
    file.close();
    return 0;
}
int SELogger::logUserMsg(QString user, QString message){
    QFile file(ffilename);
    if (!file.open(QIODevice::Append | QIODevice::Text)){
        return -1;
    }
    QTextStream out(&file);
    out << message << " occured for " << user << " at " << formatTime("yyyMMdd_hh:mm:ss") << Qt::endl;
    file.close();
    return 0;
}
int SELogger::OpenFile(){
    QFile file(ffilename);
    if (file.open(QIODevice::Append | QIODevice::Text)){
        ffile.setDevice(&file);
        qDebug() << "file opened";
    }
    else{
        qDebug() << "file not opened";
        return 1;
    }
    return 0;
}

