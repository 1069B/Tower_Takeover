#include "robot/graphical/rectangleClass.h"

Rectangle::Rectangle(PassInfo& info){
  m_xOrgin = info.xOrgin; //Every thing is in realtion to the upper left coner
  m_yOrgin = info.yOrgin;
  m_length = info.length;
  m_width = info.width;
  m_mode = info.mode;
  if(m_mode)
    m_lv_styleFunction = info.lv_styleFunction;
  else
    m_style1 = info.style1;
}

void Rectangle::draw(){
  m_obj1 = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(m_obj1, m_length, m_width);
  lv_obj_set_style(m_obj1, m_style1);
  lv_obj_align(m_obj1, NULL, LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  m_state = true;
}

void Rectangle::update(){
  if(m_state && m_mode){
    m_style1 = m_lv_styleFunction();
    lv_obj_set_style(m_obj1, m_style1);
  }
}

void Rectangle::remove(){
  if(m_state){
    lv_obj_del(m_obj1);
    m_state = false;
  }
}
