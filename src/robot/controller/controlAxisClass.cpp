#include "robot/controller/controlAxisClass.h"

ControlAxis::ControlAxis(pros::controller_id_e_t p_controller, pros::controller_analog_e_t p_type){
  m_controllerType = p_controller;
  m_axisType = p_type;
}

void ControlAxis::setMultiplier(int p_mult){
  m_multiplier = p_mult;
}

int ControlAxis::getValue(){
  return (pros::c::controller_get_analog(m_controllerType, m_axisType) * m_multiplier);
}

int ControlAxis::getPercent(){
  return ((pros::c::controller_get_analog(m_controllerType, m_axisType)/1.27) * m_multiplier);
}
