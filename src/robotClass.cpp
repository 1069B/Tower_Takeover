#include "robotClass.hpp"

Robot::Robot():
  m_gui("Home"),
  m_mainController(pros::E_CONTROLLER_MASTER),
  m_partnerController(pros::E_CONTROLLER_PARTNER),
  m_timer(),
  m_config("Robot_Config.txt"),
  Enc1("Enc1", 1, false),
  m_base(*this, HOLONOMIC, ACTIVE_CORRECTIONS, true)
  {
    if(m_config.varExist("Comp_Mode"))
      m_compMode = m_config.readString("Comp_Mode");
    else
      m_compMode = "DriverControl";



    defineGUI();
    m_base.initialize();

    m_partnerController.Axis2.setMultiplier(1);
}

Motor Tray_Motor("Tray", 5, pros::E_MOTOR_GEARSET_36, false);

Motor Left_Intake_Motor("Left_Intake", 6, pros::E_MOTOR_GEARSET_36, false);

Motor Right_Intake_Motor("Right_Intake", 7, pros::E_MOTOR_GEARSET_36, false);

Motor Justin_Trudeau("Justin_Trudeau", 8, pros::E_MOTOR_GEARSET_36, false);

int Robot::task(){
  m_gui.task();
  m_mainController.callBackCheck();
  m_partnerController.callBackCheck();

  Tray_Motor.setVelocity(m_partnerController.Axis2.getValue());
  Left_Intake_Motor.setVelocity(m_partnerController.Axis3.getValue());
  Right_Intake_Motor.setVelocity(m_partnerController.Axis3.getValue());
  Justin_Trudeau.setVelocity(m_partnerController.Axis4.getValue());

  m_base.driverControl();

  return 0;
}
