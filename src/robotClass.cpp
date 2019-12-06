#include "robotClass.hpp"

Motor Tray_Motor("Tray", 5, pros::E_MOTOR_GEARSET_36, false);

Motor Left_Intake_Motor("Left_Intake", 6, pros::E_MOTOR_GEARSET_36, true);

Motor Right_Intake_Motor("Right_Intake", 7, pros::E_MOTOR_GEARSET_36, true);

Motor Justin_Trudeau("ArmMotor", 8, pros::E_MOTOR_GEARSET_36, false);

Robot::Robot():
  m_gui("Home"),
  m_mainController(pros::E_CONTROLLER_MASTER),
  m_partnerController(pros::E_CONTROLLER_PARTNER),
  m_timer(),
  m_config("Robot_Config.txt"),
  m_base(*this, HOLONOMIC, ACTIVE_CORRECTIONS, true),
  m_tray(*this),
  m_intakeArm(*this),
  m_leftIntake(*this),
  m_rightIntake(*this)
  {
    if(m_config.varExist("Comp_Mode"))
      m_compMode = m_config.readString("Comp_Mode");
    else
      m_compMode = "DriverControl";

    m_base.initialize();

    m_tray.initialize("Tray", 5, 0, 245, true);
    m_intakeArm.initialize("ArmMotor", 8, 0, 700, false);
    m_leftIntake.initialize("Left_Intake", 6, true);
    m_rightIntake.initialize("Right_Intake", 7, false);

    m_partnerController.Axis2.setMultiplier(2);
    m_partnerController.Axis3.setMultiplier(2);

    defineGUI();
}



int Robot::task(){
  m_gui.task();
  m_mainController.callBackCheck();
  m_partnerController.callBackCheck();

  m_leftIntake.setVelocity(m_partnerController.Axis3.getValue());
  m_rightIntake.setVelocity(m_partnerController.Axis2.getValue());

  if(m_partnerController.ButtonL1.state() == true)
    m_tray.setVelocity(-100);
  else if(m_partnerController.ButtonL2.state() == true)
    m_tray.setVelocity(100);
  else
    m_tray.setVelocity(0);

  if(m_partnerController.ButtonR1.state() == true)
    m_intakeArm.setVelocity(100);
  else if(m_partnerController.ButtonR2.state() == true)
    m_intakeArm.setVelocity(-100);
  else
    m_intakeArm.setVelocity(0);

  m_base.driverControl();
  m_leftIntake.driverControl();
  m_rightIntake.driverControl();
  m_tray.driverControl();
  m_intakeArm.driverControl();

  return 0;
}

graphicalInterface& Robot::getGUI(){
  return m_gui;
}

int Robot::autonmous(){
  m_base.autonomous();
  return 0;
}
