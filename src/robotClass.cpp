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
  m_base(*this, HOLONOMIC, ACTIVE_CORRECTIONS, false)
  {
    if(m_config.varExist("Comp_Mode"))
      m_compMode = m_config.readString("Comp_Mode");
    else
      m_compMode = "DriverControl";

    m_base.initialize();

    m_partnerController.Axis2.setMultiplier(1);
    m_partnerController.Axis3.setMultiplier(2);
    Justin_Trudeau.setBrake(pros::E_MOTOR_BRAKE_HOLD);
    defineGUI();
}



int Robot::task(){
  m_gui.task();
  m_mainController.callBackCheck();
  m_partnerController.callBackCheck();

  Tray_Motor.setVelocity(m_partnerController.Axis2.getValue());
  Left_Intake_Motor.setVelocity(m_partnerController.Axis3.getValue());
  Right_Intake_Motor.setVelocity(m_partnerController.Axis3.getValue());

  if(m_partnerController.ButtonUp.state() == true)
    Justin_Trudeau.setVelocity(-200);
  else if(m_partnerController.ButtonDown.state() == true)
    Justin_Trudeau.setVelocity(200);
  else
    Justin_Trudeau.setVelocity(0);
  m_base.driverControl();

  return 0;
}

int Robot::autonmous(){
  m_base.autonomous();
  return 0;
}
