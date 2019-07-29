#include "robot/controller/controlAxisClass.h"

ControlAxis::ControlAxis(pros::controller_id_e_t controller, pros::controller_analog_e_t type){
  controllerType = controller;
  axisType = type;
}

void ControlAxis::setMultiplier(int mult){
  multiplier = mult;
}

int ControlAxis::getValue(){
  return (pros::c::controller_get_analog(controllerType, axisType) * multiplier);
}

int ControlAxis::getPercent(){
  return ((pros::c::controller_get_analog(controllerType, axisType)/1.27) * multiplier);
}
