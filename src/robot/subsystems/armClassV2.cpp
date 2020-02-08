#include "robot/subsystems/armClassV2.hpp"
#include "robot/devices/motorClass.hpp"
#include "robotClass.hpp"

ArmV2::ArmV2(Robot& p_robot) : m_robot(p_robot){

}

int ArmV2::initialize(const std::string p_armMotor, const int p_port, const int p_limitLow, const int p_limitHigh, const bool p_reversed){
  m_reversed = p_reversed;
  m_limitLow = p_limitLow;
  m_limitHigh = p_limitHigh;
  if(Motor::findMotor(p_armMotor) == NULL)
    m_armMotor = new Motor(p_armMotor,p_port,pros::E_MOTOR_GEARSET_36, p_reversed);
   else
     m_armMotor = Motor::findMotor(p_armMotor);

  m_armMotor->setBrake(m_brakeMode);

  m_armMotor->defineGUI(m_robot.getGUI(), "Home");

  return 0;
}

int ArmV2::setLimitLow(const int p_limitLow){
  m_limitLow = p_limitLow;
  return 0;
}

int ArmV2::setLimitHigh(const int p_limitHigh){
  m_limitHigh = p_limitHigh;
  return 0;
}

int ArmV2::setPreset1(const int p_preset1){
  m_preset1 = p_preset1;
  return 0;
}

int ArmV2::setPreset2(const int p_preset2){
  m_preset2 = p_preset2;
  return 0;
}

int ArmV2::setPreset3(const int p_preset3){
  m_preset3 = p_preset3;
  return 0;
}

int ArmV2::setPreset4(const int p_preset4){
  m_preset4 = p_preset4;
  return 0;
}

int ArmV2::setAccelerationCurveCoefficent(const int p_coefficeint){
  m_accelerationCurveCoefficient = p_coefficeint;
  return 0;
}

int ArmV2::setBrake(const pros::motor_brake_mode_e p_brakeMode){
  m_brakeMode = p_brakeMode;
  return 0;
}

int ArmV2::setMaximumVelcoity(const int p_velocityMax){
  m_velcoityMaximum = p_velocityMax;
  return 0;
}

/* GO TO FUNCTION */
int ArmV2::goToVelocity(const int p_velocity){//Mode 0
  m_mode = 0;
  m_desiredVelcoity = p_velocity;
  return 0;
}

int ArmV2::goToPosition(const int p_position){// Mode 1
  m_mode = 1;
  m_desiredPosition = p_position;
  return 0;
}

int ArmV2::goToLimitLow(){// Mode 2
  m_mode = 2;
  return 0;
}

int ArmV2::goToLimitHigh(){// Mode 3
  m_mode = 3;
  return 0;
}

int ArmV2::task(){
  if(m_robot.getRobotMode() == ROBOT_DISABLED){
    m_armMotor->setVelocity(0);
    m_armMotor->setBrake(m_brakeMode);
  }
  else if(m_robot.getRobotMode() == ROBOT_OPERATER || m_robot.getRobotMode() == ROBOT_AUTO){

  }

  return 0;
}
