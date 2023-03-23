#include "passwordwidget.h"
#include "ui_passwordwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QCryptographicHash>
#include <QDir>

PasswordWidget::PasswordWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PasswordWidget)
{
    ui->setupUi(this);

    // Users can only enter valid characters
    QRegularExpression re("[a-zA-Z0-9!@#$%&*]+$");
    QValidator *v2 = new QRegularExpressionValidator(re);
    ui->passwordBox->setValidator(v2);

    // Loads and hashes list of common passwords
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


PasswordWidget::~PasswordWidget()
{
    delete ui;
}


void PasswordWidget::on_runButton_clicked()
{
    operation = ui->operationList->currentText();
    password = ui->passwordBox->text();
    QString text = "";
    if (operation.contains("Validate") && operation.contains("Hash")) {
        operation = "both";
    }
    if (operation.contains("Hash") || operation.contains("both")) {
        QString hashedPassword = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());
        text.append("Hashed password (MD5): ");
        text.append(hashedPassword);
        text.append("\n");
        if (hashedList.contains(hashedPassword)) {
            text.append("Password is too common\n");
        }
    }
    ui->resultsBox->clear();
    ui->resultsBox->setText(text);
}


void PasswordWidget::on_changeSourceButton_clicked()
{
    // picks new list of hashes to compare password to
    QString sourceFile = QFileDialog::getOpenFileName(this, tr("Source File"), "C:\\", tr("*.txt"));
    QFile inputFile(sourceFile);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        hashedList.clear();
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QString hashedLine = QString(QCryptographicHash::hash((line.toUtf8()),QCryptographicHash::Md5).toHex());
            hashedList.append(hashedLine);
       }
       inputFile.close();
    }
}
