#include "robot/graphical/screenClass.hpp"

Toggle::Toggle(const PassInfo& p_info, Screen& p_screen):m_screen(p_screen){
  m_xOrgin = p_info.xOrgin;
  m_yOrgin = p_info.yOrgin;
  m_length = p_info.length;
  m_width = p_info.width;
  m_mode = p_info.mode;
  switch(m_mode){
    case 0: m_boolPointer = p_info.boolPointer; break;
    case 1: m_boolFunction = p_info.boolFunction; break;
  }
  m_state = false;
}

void Toggle::draw(){
  m_obj1 = lv_sw_create(m_screen.m_obj1, NULL);
  lv_sw_set_style(m_obj1, LV_SW_STYLE_BG, &toggleBackground);
  lv_sw_set_style(m_obj1, LV_SW_STYLE_INDIC, &toggleInactive);
  lv_sw_set_style(m_obj1, LV_SW_STYLE_KNOB_ON, &toggleOn);
  lv_sw_set_style(m_obj1, LV_SW_STYLE_KNOB_OFF, &toggleOff);
  lv_obj_align(m_obj1, NULL, LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  lv_obj_set_size(m_obj1, m_length, m_width);
  switch(m_mode){
    case 0: setState(m_boolPointer); break;
    case 1: setState(m_boolFunction()); break;
  }
  m_state = true;
}

void Toggle::remove(){
  if(m_state){
    lv_obj_del(m_obj1);
    m_state = false;
  }
}

int Toggle::getState(){
  if(m_mode == 0)
    *m_boolPointer = lv_sw_get_state(m_obj1);
  return lv_sw_get_state(m_obj1);
}

void Toggle::setState(const bool p_state){
  if(p_state)
    lv_sw_on(m_obj1);
  else
    lv_sw_on(m_obj1);
}
