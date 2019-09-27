#include "robot/controller/controlBtnClass.h"

ControlBtn::ControlBtn(pros::controller_id_e_t p_controller, pros::controller_digital_e_t p_type){
  m_controllerType = p_controller;
  m_buttonType = p_type;
}

void ControlBtn::setCallBack(std::function<void()> p_function, int p_delay){
  m_callBackState = true;
  m_callBack = p_function;
  m_callBackDelay = p_delay;
}

void ControlBtn::checkCallBack(){
  if(m_callBackState && state() && pros::millis() > m_lastCall+m_callBackDelay){
    m_callBack();
    m_lastCall = pros::millis();
  }
}

bool ControlBtn::state(){
  return pros::c::controller_get_digital(m_controllerType, m_buttonType);
}
