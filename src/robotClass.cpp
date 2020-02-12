#include "robotClass.hpp"
#include "robot/devices/motorClass.hpp"

Robot::Robot():
  m_gui("Home"),
  m_mainController(pros::E_CONTROLLER_MASTER),
  m_partnerController(pros::E_CONTROLLER_PARTNER),
  m_timer(),
  m_config("Robot_Config.txt"),
  m_base(*this, HOLONOMIC, ACTIVE_CORRECTIONS, true),
  m_tray(*this, "Tray"),
  m_slider(*this, "Slider"),
  m_leftIntake(*this),
  m_rightIntake(*this),
  m_taskScheduler(*this, "MainTaskScheduler")
  {
    // if(m_config.varExist("Comp_Mode"))
    //   m_robotMode = m_config.readString("Comp_Mode");
    // else
    //   m_robotMode = "DriverControl";

    m_base.initialize();

    m_tray.initialize("TrayMotor", 5, 0, 675, false);
    m_slider.initialize("SliderMotor", 8, 0, 680, true);
    m_leftIntake.initialize("Left_Intake", 6, true);
    m_rightIntake.initialize("Right_Intake", 9, false);

    m_partnerController.Axis2.setMultiplier(2);
    m_partnerController.Axis3.setMultiplier(2);

    m_tray.setLimitHighPreset(.25, .75, 20, 35);
    m_tray.setPreset1(650, .20, .80, 20, 35);
    m_tray.setLimitLowPreset(.25, .25, 20, 75);

    m_slider.setLimitHighPreset(.25, .25, 25, 75);
    m_slider.setPreset1(400, .25, .25, 25, 75);// High Pick Uo
    m_slider.setPreset2(600, .25, .25, 25, 75);// Low Pickup
    m_slider.setPreset3(50, .25, .25, 25, 75);//Scoreing
    m_slider.setLimitLowPreset(.25, .25, 25, 75);

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
  m_leftIntake.task();
  m_rightIntake.task();
  return 0;
}

GraphicalInterface& Robot::getGUI(){
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
  m_slider.goToVelocity(100);
  m_slider.task();
  pros::delay(1500);
  m_slider.goToVelocity(0);
  m_slider.task();
  return 0;
}

int Robot::driverControl(){
  m_leftIntake.setVelocity(m_partnerController.Axis3.getValue());
  m_rightIntake.setVelocity(m_partnerController.Axis2.getValue());

  if(m_partnerController.ButtonL1.state() == true)
    m_tray.goToVelocity(30);
  else if(m_partnerController.ButtonL2.state() == true)
    m_tray.goToVelocity(-30);
  else
    m_tray.goToVelocity(0);

  if(m_partnerController.ButtonUp.state() == true){
    m_tray.goToLimitHigh();
    m_slider.goToPreset3();
  }
  else if(m_partnerController.ButtonDown.state() == true){
    m_tray.goToLimitLow();
    m_slider.goToLimitLow();
  }



  if(m_partnerController.ButtonR1.state() == true)
    m_slider.goToVelocity(-75);
  else if(m_partnerController.ButtonR2.state() == true)
    m_slider.goToVelocity(75);
  else
    m_slider.goToVelocity(0);

  if(m_partnerController.ButtonX.state() == true){
    m_slider.goToLimitLow();
  }
  else if(m_partnerController.ButtonA.state() == true){
    m_slider.goToPreset1();
  }
  else if(m_partnerController.ButtonY.state() == true){
    m_slider.goToPreset2();
  }
  else if(m_partnerController.ButtonB.state() == true){
    m_slider.goToLimitLow();
  }
  return 0;
}

int Robot::disabled(){
  m_base.disabled();
  // m_leftIntake.disabled();
  // m_rightIntake.disabled();
  m_tray.goToVelocity(0);
  m_tray.setBrake(MOTOR_BRAKE_COAST);
  m_slider.goToVelocity(0);
  m_slider.setBrake(MOTOR_BRAKE_COAST);
  return 0;
}

RobotMode Robot::getRobotMode(){
  return m_robotMode;
}
