#include "robot/graphical/screenClass.hpp"

Meter::Meter(const PassInfo& p_info, Screen& p_screen): m_screen(p_screen){
  m_xOrgin = p_info.xOrgin;
  m_yOrgin = p_info.yOrgin;
  m_rangeLow = p_info.rangeLow;
  m_rangeHigh = p_info.rangeHigh;
  m_size = p_info.sizeFactor;
  m_angle = p_info.angle;
  m_numberOfDashes = p_info.numOfDashes;
  m_style1 = p_info.style1;// Default styles
  m_style2 = p_info.style2;
  m_intFunction = p_info.intFunction;
}

void Meter::draw(){
  m_state = true;
  m_obj1 = lv_lmeter_create(m_screen.m_obj1, NULL);
  lv_obj_set_style(m_obj1, m_style1);
  lv_lmeter_set_range(m_obj1, m_rangeLow, m_rangeHigh);
  lv_obj_set_size(m_obj1, m_size, m_size);
  lv_obj_align(m_obj1, m_screen.m_obj1, LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  lv_lmeter_set_scale(m_obj1, m_angle, m_numberOfDashes);
  lv_lmeter_set_value(m_obj1, 42);

  m_obj2 = lv_label_create(m_obj1, NULL);
  lv_label_set_text(m_obj2, "42%");
  lv_obj_set_style(m_obj2, m_style2);
  lv_obj_align(m_obj2, m_obj1, LV_ALIGN_CENTER, 0, 0);
}

void Meter::update(){
  if(m_state){
    lv_lmeter_set_value(m_obj1, m_intFunction());
    lv_label_set_text(m_obj2, std::to_string(m_intFunction()).c_str());
  }
}

void Meter::remove(){
  if(m_state){
    lv_obj_clean(m_obj1);
    lv_obj_del(m_obj1);
    m_state = false;
  }
}