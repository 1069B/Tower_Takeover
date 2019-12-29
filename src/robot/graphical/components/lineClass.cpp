#include "robot/graphical/screenClass.hpp"

Line::Line(const PassInfo& p_info, Screen& p_screen): m_screen(p_screen){
  m_points = p_info.points;
  m_style1 = p_info.style1;
}

void Line::draw(){
  m_obj1 = lv_line_create(m_screen.m_obj1, NULL);
  lv_line_set_points(m_obj1, m_points, 2);
  lv_obj_align(m_obj1, m_screen.m_obj1, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_line_set_style(m_obj1, m_style1);
  m_state = true;
}

void Line::remove(){
  if(m_state){
    lv_obj_del(m_obj1);
    m_state = false;
  }
}
