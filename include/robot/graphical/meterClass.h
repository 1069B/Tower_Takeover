#include "styles.h"
#include "abstractClass.h"

#ifndef METERCLASS_H
#define METERCLASS_H

class Meter: protected AbstractGUI{
protected:
  friend class Screen;
  int rangeLow = 0;
  int rangeHigh = 100;
  int size = 125;
  int angle = 240;
  int numberOfDashes = 22;

  Meter(PassInfo& info);

  void draw();
  void update();
  void remove();
};

#endif // METERCLASS_H
