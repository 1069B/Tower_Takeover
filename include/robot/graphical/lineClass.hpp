#include "styles.hpp"
#include "abstractClass.hpp"

#ifndef LINECLASS_H
#define LINECLASS_H

class Screen;

class Line: protected AbstractGUI{
public:
  Screen& m_screen;
  lv_point_t* m_points;// Attempt to use xOrg yOrg etc
  Line(const PassInfo& p_info, Screen& p_screen);

  void draw();
  void remove();
};

#endif // LINECLASS_H
