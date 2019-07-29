#include "styles.h"
#include "abstractClass.h"

#ifndef RECTANGLECLASS_H
#define RECTANGLECLASS_H

class Rectangle: protected AbstractGUI{
protected:
  friend class Screen;
  Rectangle(PassInfo& info);

  void draw();
  void update();
  void remove();
};

#endif // RECTANGLECLASS_H
