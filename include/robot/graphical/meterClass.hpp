#include "styles.h"
#include "abstractClass.h"

#ifndef METERCLASS_H
#define METERCLASS_H

class Meter: protected AbstractGUI{
protected:
  friend class Screen;
  int m_rangeLow = 0;
  int m_rangeHigh = 100;
  int m_size = 125;
  int m_angle = 240;
  int m_numberOfDashes = 22;

  Meter(const PassInfo& p_info);

  void draw();
  void update();
  void remove();
};

#endif // METERCLASS_H
