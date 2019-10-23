#include "robotClass.hpp"

Robot::Robot():
  m_gui("Home"),
  m_mainController(pros::E_CONTROLLER_MASTER),
  m_partnerController(pros::E_CONTROLLER_PARTNER),
  m_timer(),
  m_config("Robot_Config.txt"),
  Enc1("Enc1", 1, false),
  m_base(HOLONOMIC, ACTIVE_CORRECTIONS, true, m_mainController, m_partnerController)
  {
    if(m_config.fileExist()){
      m_compMode = m_config.readString("Comp_Mode");
      m_baseType = m_config.readString("Base_Type");
    }
    defineGUI();

    m_base.defineHolonomic("BaseFrontLeft", "BaseFrontRight" , "BaseBackLeft", "BaseBackRight");

    m_mainController.Axis1.setMultiplier(2);
    m_mainController.Axis2.setMultiplier(2);
    m_mainController.Axis3.setMultiplier(2);
    m_mainController.Axis4.setMultiplier(2);

    m_partnerController.Axis2.setMultiplier(1);
}

Motor Tray_Motor("Tray", 5, pros::E_MOTOR_GEARSET_36, false);


int Robot::task(){
  m_gui.task();
  m_mainController.callBackCheck();
  m_partnerController.callBackCheck();

  Tray_Motor.setVelocity(m_partnerController.Axis2.getValue());

  m_base.driverControl();

  return 0;
}
