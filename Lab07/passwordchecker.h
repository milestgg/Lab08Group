#ifndef PASSWORDCHECKER_H
#define PASSWORDCHECKER_H

#include <QMainWindow>
#include <QCryptographicHash>

QT_BEGIN_NAMESPACE
namespace Ui { class PasswordChecker; }
QT_END_NAMESPACE

//class definition
class PasswordChecker : public QMainWindow
{
    Q_OBJECT

    //public class constructors...
public:
    PasswordChecker(QWidget *parent = nullptr);
    ~PasswordChecker();

    //name private slots...
private slots:
    void on_HelpButton_clicked();
    void on_Exit_AppButton_clicked();
    void on_Complexity_CheckButton_clicked();
    void on_Hash_CompareButton_clicked();
    void on_Hash_ComplexityButton_clicked();

    //private class constructors
private:
    Ui::PasswordChecker *ui;

    int calculatePasswordScore(const QString& password);
    QByteArray calculatePasswordHash(const QString& password);
};

#endif // PASSWORDCHECKER_H
