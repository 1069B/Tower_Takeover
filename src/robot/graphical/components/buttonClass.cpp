#include "robot/graphical/screenClass.hpp"

Button::Button(const PassInfo& p_info, Screen& p_screen):
m_timer(false), m_screen(p_screen),m_nextScreenVar(p_screen.m_nextScreenID){
  m_xOrgin = p_info.xOrgin; //Every thing is in realtion to the upper left coner
  m_yOrgin = p_info.yOrgin;
  m_length = p_info.length;
  m_width = p_info.width;
  m_style1 = p_info.style1;
  m_style2 = p_info.style2;
  m_format = p_info.text;
}

void Button::defineAction(const PassInfo& p_info){
  m_mode = p_info.mode;
  switch(m_mode){
    case 0:
      m_linkedScreenID = p_info.linkedID;
      m_changeScreen = true;
      break;
    case 1:
      m_intPointer = p_info.intPointer;
      m_value = p_info.passValue;
      m_changeVar = true;
      break;
    case 2:
      m_intPointer = p_info.intPointer;
      m_value = p_info.passValue;
      m_incrementVar = true;
      break;
  }
}

void Button::draw() {
  m_obj1 = lv_btn_create(m_screen.m_obj1, NULL);
  m_obj2 = lv_label_create(m_obj1, NULL);
  lv_obj_align(m_obj1, m_screen.m_obj1, LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  lv_obj_set_free_num(m_obj1, m_id);   /*Set a unique number for the button*/
  lv_obj_set_size(m_obj1, m_length, m_width); //set the button size
  lv_btn_set_style(m_obj1, LV_BTN_STYLE_REL, m_style1); //set the relesed style
  lv_btn_set_style(m_obj1, LV_BTN_STYLE_PR, m_style2); //set the pressed style
  lv_label_set_text(m_obj2, m_format.c_str());
  m_state = true;
}

void Button::update(){
  lv_label_set_text(m_obj2, m_format.c_str());
}

void Button::remove() {
  if(m_state){
    lv_obj_clean(m_obj1);
    lv_obj_del(m_obj1);
    m_state = false;
  }
}

void Button::checkState(){
  if(m_state && m_timer.preformAction()){
    lv_btn_state_t buttonState = lv_btn_get_state(m_obj1);
    if(buttonState == LV_BTN_STATE_PR){
      if(m_changeVar){
        *m_intPointer = m_value;
      }
      else if(m_incrementVar){
        *m_intPointer += m_value;
      }

      if(m_changeScreen){
        m_nextScreenVar = m_linkedScreenID;
      }
      m_timer.addActionDelay(500);
      return;
    }
  }
}

bool Button::returnState(){
  if(m_state && m_timer.preformAction()){
    lv_btn_state_t buttonState = lv_btn_get_state(m_obj1);
    if(buttonState == LV_BTN_STATE_PR){
      m_timer.addActionDelay(500);
      return true;
    }
  }
  return false;
}
