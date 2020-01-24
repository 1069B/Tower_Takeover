#include "robotClass.hpp"

Robot::Robot():
  m_gui("Home"),
  m_mainController(pros::E_CONTROLLER_MASTER),
  m_partnerController(pros::E_CONTROLLER_PARTNER),
  m_timer(),
  m_config("Robot_Config.txt"),
  m_base(*this, HOLONOMIC, ACTIVE_CORRECTIONS, true),
  m_tray(*this),
  m_slider(*this),
  m_leftIntake(*this),
  m_rightIntake(*this),
  m_taskScheduler(*this, "MainTaskScheduler")
  {
    if(m_config.varExist("Comp_Mode"))
      m_compMode = m_config.readString("Comp_Mode");
    else
      m_compMode = "DriverControl";

    m_base.initialize();

    m_tray.initialize("TrayMotor", 5, 0, 675, false);
    m_slider.initialize("SliderMotor", 8, 0, 710, true);
    m_leftIntake.initialize("Left_Intake", 6, true);
    m_rightIntake.initialize("Right_Intake", 7, false);

    m_partnerController.Axis2.setMultiplier(2);
    m_partnerController.Axis3.setMultiplier(2);

    defineGUI();
}

int Robot::task(){
  m_taskScheduler.task();
  m_gui.task();
  m_mainController.callBackCheck();
  m_partnerController.callBackCheck();

  m_tray.task();
  m_slider.task();

  m_base.driverControl();
  m_leftIntake.driverControl();
  m_rightIntake.driverControl();
  return 0;
}

graphicalInterface& Robot::getGUI(){
  return m_gui;
}

TaskScheduler& Robot::getTaskScheduler(){
  return m_taskScheduler;
}

int Robot::autonmous(){
  //m_base.autonomous();
  m_base.m_frontRightMotor->setVelocity(75);
  m_base.m_frontLeftMotor->setVelocity(75);
  m_base.m_backRightMotor->setVelocity(75);
  m_base.m_backLeftMotor->setVelocity(75);
  pros::delay(750);
  m_base.m_frontRightMotor->setVelocity(-75);
  m_base.m_frontLeftMotor->setVelocity(-75);
  m_base.m_backRightMotor->setVelocity(-75);
  m_base.m_backLeftMotor->setVelocity(-75);
  pros::delay(1000);
  m_base.m_frontRightMotor->setVelocity(0);
  m_base.m_frontLeftMotor->setVelocity(0);
  m_base.m_backRightMotor->setVelocity(0);
  m_base.m_backLeftMotor->setVelocity(0);
  m_slider.setVelocity(100);
  m_slider.task();
  pros::delay(1500);
  m_slider.setVelocity(0);
  m_slider.task();
  return 0;
}

int Robot::driverControl(){
  m_leftIntake.setVelocity(m_partnerController.Axis3.getValue());
  m_rightIntake.setVelocity(m_partnerController.Axis2.getValue());

  if(m_partnerController.ButtonL1.state() == true)
    m_tray.setVelocity(50);
  else if(m_partnerController.ButtonL2.state() == true)
    m_tray.setVelocity(-50);
  else
    m_tray.setVelocity(0);

  if(m_partnerController.ButtonR1.state() == true)
    m_slider.setVelocity(-100);
  else if(m_partnerController.ButtonR2.state() == true)
    m_slider.setVelocity(100);
  else
    m_slider.setVelocity(0);
  return 0;
}

int Robot::disabled(){
  m_base.disabled();
  m_leftIntake.disabled();
  m_rightIntake.disabled();
  m_tray.setVelocity(0);
  m_tray.setBrake(MOTOR_BRAKE_COAST);
  m_slider.setVelocity(0);
  m_slider.setBrake(MOTOR_BRAKE_COAST);
  return 0;
}
