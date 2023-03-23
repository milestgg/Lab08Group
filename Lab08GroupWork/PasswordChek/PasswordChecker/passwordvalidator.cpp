#include "passwordvalidator.h"
#include <QRegularExpression>
PasswordValidator::PasswordValidator()
{

}

bool PasswordValidator::validatePassword(QString pass){
    int minlen = 8;
    if (pass.length() < minlen){

    }
    QRegularExpression upperCase("[A-Z]");
    QRegularExpression lowerCase("[a-z]");
    //digit
    QRegularExpression digit("\\d");
    QRegularExpression specialChar("[!@#$%&*]");

    bool upper = pass.contains(upperCase);
    bool lower = pass.contains(lowerCase);
    bool digi = pass.contains(digit);
    bool spec = pass.contains(specialChar);
    if(upper && lower &&digi && spec){
        return true;
    }
    return false;
}
