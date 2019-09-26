#include "robot/graphical/labelClass.h"

Label::Label(PassInfo& p_info){// mode 0
  m_xOrgin = p_info.xOrgin;
  m_yOrgin = p_info.yOrgin;
  m_style1 = p_info.style1;
  m_format[0] = p_info.text;
  m_mode = p_info.mode;
  switch(m_mode){
    case 0: break;
    case 1: m_intPointer = p_info.intPointer; break;
    case 2: m_intFunction = p_info.intFunction; break;
    case 3: m_doublePointer = p_info.doublePointer; break;
    case 4: m_doubleFunction = p_info.doubleFunction; break;
    case 5: m_boolPointer = p_info.boolPointer; break;
    case 6: m_boolFunction = p_info.boolFunction; break;
    case 7: m_stringPointer = p_info.stringPointer; break;
    case 8: m_stringFunction = p_info.stringFunction; break;
  }
}

void Label::setString(){
  std::string fmt = m_format[0];
  std::string sum = "";
  switch(m_mode){
    case 0:
      sum = fmt;
      break;
    case 1:
      sum = fmt.substr(0, fmt.find("%d")) + std::to_string(*m_intPointer) + fmt.substr(fmt.find("%d")+2);
      break;
    case 2:
      sum = fmt.substr(0, fmt.find("%d")) + std::to_string(m_intFunction()) + fmt.substr(fmt.find("%d")+2);
      break;
    case 3:
      sum = fmt.substr(0, fmt.find("%f")) + std::to_string(*m_doublePointer) + fmt.substr(fmt.find("%f")+2);
      break;
    case 4:
      sum = fmt.substr(0, fmt.find("%f")) + std::to_string(m_doubleFunction()) + fmt.substr(fmt.find("%f")+2);
      break;
    case 5:
      if(*m_boolPointer)
        sum = fmt.substr(0, fmt.find("%b")) + "True" + fmt.substr(fmt.find("%b")+2);
      else
        sum = fmt.substr(0, fmt.find("%b")) + "False" + fmt.substr(fmt.find("%b")+2);
      break;
    case 6:
      if(m_boolFunction())
        sum = fmt.substr(0, fmt.find("%b")) + "True" + fmt.substr(fmt.find("%b")+2);
      else
        sum = fmt.substr(0, fmt.find("%b")) + "False" + fmt.substr(fmt.find("%b")+2);
      break;
    case 7:
      sum = fmt.substr(0, fmt.find("%s")) + *m_stringPointer + fmt.substr(fmt.find("%s")+2);
      break;
    case 8:
      sum = fmt.substr(0, fmt.find("%s")) + m_stringFunction() + fmt.substr(fmt.find("%s")+2);
      break;
  }
  lv_label_set_text(m_obj1, sum.c_str());
}

void Label::draw(){
  m_obj1 = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(m_obj1, NULL, LV_ALIGN_IN_TOP_LEFT, m_xOrgin, m_yOrgin);
  setString();
  lv_obj_set_style(m_obj1, m_style1);
  m_state = true;
}
void Label::update(){
  if(m_state){
    setString();
  }
}
void Label::remove(){
  if(m_state){
    lv_obj_del(m_obj1);
    m_state = false;
  }
}
