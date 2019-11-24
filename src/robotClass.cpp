#include "robotClass.hpp"

Robot::Robot():
  m_gui("Home"),
  m_mainController(pros::E_CONTROLLER_MASTER),
  m_partnerController(pros::E_CONTROLLER_PARTNER),
  m_timer(),
  m_config("Robot_Config.txt"),
  m_base(*this, HOLONOMIC, ACTIVE_CORRECTIONS, false),
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

    m_tray.initialize("Tray", 5, 0, 500, false);
    m_intakeArm.initialize("ArmMotor", 8, 0, 500, false);
    m_leftIntake.initialize("Left_Intake", 6, true);
    m_rightIntake.initialize("Right_Intake", 7, false);

    m_partnerController.Axis2.setMultiplier(1);
    m_partnerController.Axis3.setMultiplier(2);

    defineGUI();
}

int Robot::task(){
  m_gui.task();
  m_mainController.callBackCheck();
  m_partnerController.callBackCheck();

  m_tray.setVelocity(m_partnerController.Axis2.getValue());
  m_leftIntake.setVelocity(m_partnerController.Axis3.getValue());
  m_rightIntake.setVelocity(m_partnerController.Axis3.getValue());

  if(m_partnerController.ButtonUp.state() == true)
    m_intakeArm.setVelocity(-200);
  else if(m_partnerController.ButtonDown.state() == true)
    m_intakeArm.setVelocity(200);
  else
    m_intakeArm.setVelocity(0);

  m_base.driverControl();

  return 0;
}

int Robot::autonmous(){
  m_base.autonomous();
  return 0;
}
