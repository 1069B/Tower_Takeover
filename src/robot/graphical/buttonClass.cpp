#include "robot/graphical/buttonClass.h"

Button::Button(const PassInfo& p_info, std::string& p_nextScreenID):m_timer(false), m_varible(*p_info.intPointer), m_nextScreenVar(p_nextScreenID){
  m_id = p_info.id; // Id for the Button
  m_xOrgin = p_info.xOrgin; //Every thing is in realtion to the upper left coner
  m_yOrgin = p_info.yOrgin;
  m_length = p_info.length;
  m_width = p_info.width;
  m_style1 = p_info.style1;
  m_style2 = p_info.style2;
}

void Button::defineAction(const PassInfo& p_info){
  m_mode = p_info.mode;
  m_linkedScreenID[p_info.version] = p_info.linkedID;// Corasponding screen
  m_value[p_info.version] = p_info.passValue; //Value set to above varible
  m_format[p_info.version] = p_info.text;
}

void Button::draw(const int p_btnVer) {
  m_obj1 = lv_btn_create(lv_scr_act(), NULL);
  m_obj2 = lv_label_create(m_obj1, NULL);
  lv_obj_align(m_obj1, NULL, LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  lv_obj_set_free_num(m_obj1, m_id);   /*Set a unique number for the button*/
  lv_obj_set_size(m_obj1, m_length, m_width); //set the button size
  lv_btn_set_style(m_obj1, LV_BTN_STYLE_REL, m_style1); //set the relesed style
  lv_btn_set_style(m_obj1, LV_BTN_STYLE_PR, m_style2); //set the pressed style
  lv_label_set_text(m_obj2, m_format[p_btnVer].c_str());
  m_state = true;
}

void Button::update(const int p_btnVer){
  lv_label_set_text(m_obj2, m_format[p_btnVer].c_str());
}

void Button::remove() {
  if(m_state){
    lv_obj_clean(m_obj1);
    lv_obj_del(m_obj1);
    m_state = false;
  }
}

void Button::checkState(const int p_btnVer){
  if(m_state && m_timer.preformAction()){
    lv_btn_state_t buttonState = lv_btn_get_state(m_obj1);
    if(buttonState == LV_BTN_STATE_PR){
      m_nextScreenVar = m_linkedScreenID[p_btnVer];
      if(m_mode == 0)
        m_varible = m_value[p_btnVer];
      else if(m_mode == 1)
        m_varible += m_value[p_btnVer];

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
