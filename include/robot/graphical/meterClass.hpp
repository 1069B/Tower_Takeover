#include "styles.hpp"
#include "abstractClass.hpp"

#ifndef METERCLASS_H
#define METERCLASS_H

class Screen;

class Meter: protected AbstractGUI{
public:
  Screen& m_screen;
  int m_rangeLow = 0;
  int m_rangeHigh = 100;
  int m_size = 125;
  int m_angle = 240;
  int m_numberOfDashes = 22;

  Meter(const PassInfo& p_info, Screen& p_screen);

  void draw();
  void update();
  void remove();
};

#endif // METERCLASS_H
