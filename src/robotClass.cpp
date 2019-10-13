#include "robotClass.hpp"

Robot::Robot():
  m_gui("Home"),
  m_mainController(pros::E_CONTROLLER_MASTER),
  m_partnerController(pros::E_CONTROLLER_PARTNER),
  m_timer(),
  m_config("Robot_Config.txt"){
    if(m_config.fileExist()){
      m_compMode = m_config.readString("Comp_Mode");
      m_baseType = m_config.readString("Base_Type");
    }
    defineGUI();
}

int Robot::task(){
  m_gui.task();
  m_mainController.callBackCheck();
  m_partnerController.callBackCheck();
  return 0;
}
