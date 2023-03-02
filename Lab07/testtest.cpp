#include <QObject>
#include <QTest>
#include <iostream>
#include "SE_TestInputValidation.h"
#include "SE_TestLogger.h"


int main(int argc, char **argv) {

  int tstat = 0; // default test status is 0 (success)

  
  tstat += QTest::qExec(new SE_TestInputValidation, argc, argv);
  tstat += QTest::qExec(new SE_TestLogger, argc, argv);

  std::cout << "Final result: "<<tstat<<" errors\n";
  
  return tstat;
}
