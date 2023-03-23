#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H

#include <QWidget>
#include <QFile>
#include <QList>


QT_BEGIN_NAMESPACE
namespace Ui { class PasswordWidget; }
QT_END_NAMESPACE

class PasswordWidget : public QWidget
{
    Q_OBJECT

public:
    PasswordWidget(QWidget *parent = nullptr);
    ~PasswordWidget();

    int charLength;
    int requiredLength;
    QString operation;
    QString password;
    QList<QString> hashedList;

private slots:
    void on_runButton_clicked();

    void on_changeSourceButton_clicked();

private:
    Ui::PasswordWidget *ui;
};
#endif // PASSWORDWIDGET_H
