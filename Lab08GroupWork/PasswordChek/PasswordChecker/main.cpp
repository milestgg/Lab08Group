#include "passwordchecker.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PasswordChecker w;
    w.show();
    return a.exec();
}
