#include "robot/graphical/lineClass.h"

Line::Line(PassInfo& info){
  points = info.points;
  style1 = info.style1;
}

void Line::draw(){
  obj1 = lv_line_create(lv_scr_act(), NULL);
  lv_line_set_points(obj1, points, 2);
  lv_obj_align(obj1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_line_set_style(obj1, style1);
  state = true;
}

void Line::remove(){
  if(state){
    lv_obj_del(obj1);
    state = false;
  }
}
