#include "robot/graphical/lineClass.h"

Line::Line(PassInfo& p_info){
  m_points = p_info.points;
  m_style1 = p_info.style1;
}

void Line::draw(){
  m_obj1 = lv_line_create(lv_scr_act(), NULL);
  lv_line_set_points(m_obj1, m_points, 2);
  lv_obj_align(m_obj1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_line_set_style(m_obj1, m_style1);
  m_state = true;
}

void Line::remove(){
  if(m_state){
    lv_obj_del(m_obj1);
    m_state = false;
  }
}
