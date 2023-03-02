#pragma once

#include <QTest>
#include "SELogger.h" 

class SE_TestLogger: public QObject {

  Q_OBJECT
private slots:

  void testOverloadedConstructorError();
  void testOverloadedConstructorSucess();
  void funcThree();
  
};

