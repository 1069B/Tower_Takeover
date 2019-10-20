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

    m_mainController.Axis1.setMultiplier(1);
    m_mainController.Axis2.setMultiplier(2);
    m_mainController.Axis3.setMultiplier(2);
    m_mainController.Axis4.setMultiplier(2);
}

Motor FR_Motor("FR", 1, pros::E_MOTOR_GEARSET_18, true);
Motor FL_Motor("FL", 2, pros::E_MOTOR_GEARSET_18, false);
Motor BR_Motor("BR", 3, pros::E_MOTOR_GEARSET_18, true);
Motor BL_Motor("BL", 4, pros::E_MOTOR_GEARSET_18, false);

int Robot::task(){
  m_gui.task();
  m_mainController.callBackCheck();
  m_partnerController.callBackCheck();

  int turnFactorLeft = 1 + (m_mainController.Axis1.getValue()/100);
  int turnFactorRight = 1 - (m_mainController.Axis1.getValue()/100);

  FR_Motor.setVelocity((m_mainController.Axis3.getValue()-m_mainController.Axis4.getValue()) *turnFactorLeft);
  FL_Motor.setVelocity((m_mainController.Axis3.getValue()+m_mainController.Axis4.getValue()) *turnFactorRight);
  BR_Motor.setVelocity((m_mainController.Axis3.getValue()+m_mainController.Axis4.getValue()) *turnFactorLeft);
  BL_Motor.setVelocity((m_mainController.Axis3.getValue()-m_mainController.Axis4.getValue()) *turnFactorRight);
  return 0;
}
