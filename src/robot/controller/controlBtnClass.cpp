#include "robot/controller/controlBtnClass.h"

ControlBtn::ControlBtn(pros::controller_id_e_t controller, pros::controller_digital_e_t type){
  controllerType = controller;
  buttonType = type;
}

void ControlBtn::setCallBack(std::function<void()> func, int delay){
  callBackState = true;
  callBack = func;
  callBackDelay = delay;
}

void ControlBtn::checkCallBack(){
  if(callBackState && state() && pros::millis() > lastCall+callBackDelay){
    callBack();
    lastCall = pros::millis();
  }
}

bool ControlBtn::state(){
  return pros::c::controller_get_digital(controllerType, buttonType);
}
