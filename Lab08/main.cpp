#include "passwordwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PasswordWidget w;
    w.show();
    return a.exec();
}
