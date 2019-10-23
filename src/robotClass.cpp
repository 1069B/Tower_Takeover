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
    if(m_config.varExist("Comp_Mode"))
      m_compMode = m_config.readString("Comp_Mode");
    else
      m_compMode = "DriverControl";

    if(m_config.varExist("Base_Type"))
      m_baseType = (BaseType)m_config.readInt("Base_Type");
    else
      m_baseType = HOLONOMIC;

    defineGUI();

    if(m_baseType == HOLONOMIC)
      m_base.defineHolonomic("BaseFrontLeft", "BaseFrontRight" , "BaseBackLeft", "BaseBackRight");
    else if(m_baseType == HBASE)
      m_base.defineHBase("BaseBackLeft", "BaseBackRight", "BaseCenter");
    else if(m_baseType == MECANUM)
      m_base.defineMecanum("BaseFrontLeft", "BaseFrontRight" , "BaseBackLeft", "BaseBackRight");
    else if(m_baseType == TANK2)
      m_base.defineTank2("BaseBackLeft", "BaseBackRight");
    else if(m_baseType == TANK4)
      m_base.defineTank4("BaseFrontLeft", "BaseFrontRight" , "BaseBackLeft", "BaseBackRight");

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
