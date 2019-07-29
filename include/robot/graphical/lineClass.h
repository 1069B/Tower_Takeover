#include "styles.h"
#include "abstractClass.h"

#ifndef LINECLASS_H
#define LINECLASS_H

class Line: protected AbstractGUI{
protected:
  friend class Screen;
  lv_point_t* points;// Attempt to use xOrg yOrg etc
  Line(PassInfo& info);

  void draw();
  void remove();
};

#endif // LINECLASS_H
