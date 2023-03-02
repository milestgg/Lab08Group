#include "sevalidator.h"
#include "SE_TestInputValidation.h"


/*Received help from 2/c jake carpenter*/

void SE_TestInputValidation::funcOne() {
    SEValidator pass;
    SEValidator fail;
    int passresult = pass.validateInt(20, 0,100);
    int failresult = fail.validateInt(20,200,300);

    QCOMPARE_EQ(passresult,1);

    QCOMPARE_EQ(failresult,0);

}

void SE_TestInputValidation::funcTwo() {
    SEValidator pass;
    SEValidator fail;
    int passresult = pass.validateDouble(20.4, 0.5,100.4);
    int failresult = fail.validateDouble(20.2,200.4,300.6);

    QCOMPARE_EQ(passresult,1);

    QCOMPARE_EQ(failresult,0);

}

void SE_TestInputValidation::funcThree() {
    SEValidator pass;
    SEValidator fail;
    int passresult = pass.validateString("pass");
    int failresult = fail.validateString("");

    QCOMPARE_EQ(passresult,1);

    QCOMPARE_EQ(failresult,0);

}


/****************************************
 * Make valid runnable test:
 ****************************************/

//QTEST_MAIN(SE_TestInputValidation)
#include "SE_TestInputValidation.moc"

