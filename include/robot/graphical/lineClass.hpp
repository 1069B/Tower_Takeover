#include "styles.hpp"
#include "abstractClass.hpp"

#ifndef LINECLASS_H
#define LINECLASS_H

class Line: protected AbstractGUI{
public:
  //friend class Screen;
  lv_point_t* m_points;// Attempt to use xOrg yOrg etc
  Line(const PassInfo& p_info);

  void draw();
  void remove();
};

#endif // LINECLASS_H
