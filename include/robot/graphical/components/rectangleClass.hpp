#include "abstractClass.hpp"

#ifndef RECTANGLECLASS_H
#define RECTANGLECLASS_H

class Screen;

class Rectangle: protected AbstractGUI{
public:
  Screen& m_screen;
  Rectangle(const PassInfo& p_info, Screen& p_screen);

  void draw();
  void update();
  void remove();
};

#endif // RECTANGLECLASS_H
