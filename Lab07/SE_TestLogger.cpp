#include "SE_TestLogger.h"
#include "selogger.h"
#include <QTest>
#include <iostream>


void initTestCase() {

       /* Will be called before the first test function is executed.
          This would be a good location to perform file system setup for testing.
        */

}

void init() {

    /*  Will be called before each test function is executed.
        This could be use to clean out files after each run */

}

void SE_TestLogger::testOverloadedConstructorError() {

}

void SE_TestLogger::testOverloadedConstructorSucess() {


}

void SE_TestLogger::funcThree() {



}


/****************************************
 * Make valid runnable test:
 ****************************************/

//QTEST_MAIN(SE_TestLogger)
#include "SE_TestLogger.moc"

