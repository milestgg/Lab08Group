#include "passwordchecker.h"
#include "ui_passwordchecker.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QStringList>
#include <QDir>

PasswordChecker::PasswordChecker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PasswordChecker)
{
    ui->setupUi(this);

    QDir::setCurrent("..");
    QFile inputFile("10kMostCommon.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd()) {
            QString line = in.readLine();
            QString hashedLine = QString(QCryptographicHash::hash((line.toUtf8()),QCryptographicHash::Md5).toHex());
            hashedList.append(hashedLine);
       }
       inputFile.close();
    }
}

PasswordChecker::~PasswordChecker()
{
    delete ui;
}

int PasswordChecker::calculatePasswordScore(const QString& password)
{
    int score = 0;
    int length = password.length();

    // Check length give 1 point
    if (length > 15) {
        score++;
    }

    // Check complexity Give up to 2 points
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSymbol = false;
//upper/lower/digit/special character test
    for (int i = 0; i < length; i++) {
        if (password[i].isUpper()) {
            hasUpper = true;
        } else if (password[i].isLower()) {
            hasLower = true;
        } else if (password[i].isDigit()) {
            hasDigit = true;
        } else if (!password[i].isLetterOrNumber()) {
            hasSymbol = true;
        }
    }

    if (hasUpper && (hasLower || hasDigit || hasSymbol)) {
        score += 2;
    }

    // Cap score at 4
    score = qMin(score, 4);

    return score;
}

QByteArray PasswordChecker::calculatePasswordHash(const QString& password)
{
    // Hash password using QT Built in Hash program
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hashedPassword;
}

void PasswordChecker::on_HelpButton_clicked()
{
    QMessageBox::information(this, tr("Help"), tr("Enter your password in the Password field and click on the Hash and Compare button to check if it is secure. Password score gives points based on each portion of complexity included up to a maximum of 4. Points for Length, Special Characters, Numbers, and Upper/Lowercase letters."));
}

void PasswordChecker::on_Exit_AppButton_clicked()
{
    qApp->exit();
}

void PasswordChecker::on_Complexity_CheckButton_clicked()
{
    //set initial boolean operators for characters
    QString password = ui->Password_Input->text();
    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasNumber = false;
    bool hasSpecial = false;

    if (password.length() < 15) {
        QMessageBox::critical(this, tr("Error"), tr("Password is too short. Please enter a password with at least 15 characters."));
        return;
    }
//check each character for special characters, uppercase, and lowercase
    for (int i = 0; i < password.length(); i++) {
        if (password[i].isUpper()) {
            hasUpperCase = true;
        }
        else if (password[i].isLower()) {
            hasLowerCase = true;
        }
        else if (password[i].isDigit()) {
            hasNumber = true;
        }
        else {
            hasSpecial = true;
        }
    }//use previous for loop to determine what it has, and use info to spit out requirements
    if (!hasUpperCase || !hasLowerCase || !hasNumber || !hasSpecial) {
        QMessageBox::critical(this, tr("Error"), tr("Password doesn't meet complexity requirements. Please enter a password with at least one upper and lowercase letter, one number, and one special character."));
        return;
    }
//Success message if it meets complexity requirements
    QMessageBox::information(this, tr("Success"), tr("Password meets complexity requirements."));
}

void PasswordChecker::on_Hash_ComplexityButton_clicked()
{
    QString password = ui->Password_Input->text();

    // Check password length
    if (password.length() < 15) {
        QMessageBox::warning(this, tr("Warning"), tr("Password must be at least 15 characters."));
        return;
    }

    // Check password complexity
    int score = calculatePasswordScore(password);
    if (score < 3) {
        QMessageBox::warning(this, tr("Warning"), tr("Password not complex. Make it a stronger password."));
        return;
    }

    // Check password against list of compromised passwords
    QStringList compromisedPasswords = {"password", "123456", "123456", "bababab", "abcdef"};
    QList<QByteArray> compromisedPasswordsHashed;
    //Change compromised password list to hashes...Can add more later if wanted.
    for (const auto &password : compromisedPasswords) {
        compromisedPasswordsHashed.append(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256));
    }
    QByteArray hashedPassword = calculatePasswordHash(password);
    if (compromisedPasswordsHashed.contains(QString(hashedPassword.toHex()))) {
        QMessageBox::warning(this, tr("Warning"), tr("Password is compromised. Make a better one."));
        return;
    }
    QString complexityMessage;
       if (score < 2) {
           complexityMessage = tr("Password is very weak. Please choose a stronger password.");
       } else if (score < 3) {
           complexityMessage = tr("Password is weak. Please choose a stronger password.");
       } else if (score < 4) {
           complexityMessage = tr("Password is okay, but could be stronger.");
       } else {
           complexityMessage = tr("Password is strong!");
       }
       QString message = QString("%1\n\nPassword score: %2\n").arg(complexityMessage).arg(score);
       QMessageBox::information(this, tr("Hash and Complexity Result"), message);
}
void PasswordChecker::on_Hash_CompareButton_clicked()
{
    QString password = ui->Password_Input->text();
    QString hashedPassword = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());
      if (hashedList.contains(hashedPassword)) {
            QMessageBox::warning(this, tr("Warning"), tr("Password is compromised. Make it a different password."));
            return;
        }
      else
      {
          QMessageBox::information(this, tr("Success"), tr("Password seems legit!"));
      }
}
//Couldn't get the highest level of the password score working... sad.
