#include "styles.hpp"
#include "abstractClass.hpp"

#ifndef RECTANGLECLASS_H
#define RECTANGLECLASS_H

class Rectangle: protected AbstractGUI{
protected:
  friend class Screen;
  Rectangle(const PassInfo& p_info);

  void draw();
  void update();
  void remove();
};

#endif // RECTANGLECLASS_H
