#include "robot/subsystems/intakeClass.hpp"
#include "robotClass.hpp"

Intake::Intake(Robot& p_robot): m_robot(p_robot){

}

ExternalFile Intake::m_config("Intake_Config.txt");

int Intake::setVelocity(const int p_velocity){
  m_velocity = p_velocity;
  m_intakeState = VELOCITY_DEPENDENT;
  return 0;
}

int Intake::setMovementDuration(const int p_velocity, const int p_duration){
  m_velocity = p_velocity;
  m_intakeState = TIME_DEPENDENT;
  m_timer.addActionDelay(p_duration);
  return 0;
}

int Intake::moveToPosition(const int p_velocity, const int p_position){
  m_velocity = p_velocity;
  m_targetPosition = p_position;
  m_intakeState = ENCODER_DEPENDENT;
  return 0;
}

int Intake::resetEncoder(){
  m_intakeMotor->resetRotation();
  return 0;
}

int Intake::initialize(const std::string p_intakeMotor, const int p_port, const bool p_reversed){
  m_reversed = p_reversed;
  if(Motor::findMotor(p_intakeMotor) == NULL)
    m_intakeMotor = new Motor(p_intakeMotor, p_port, pros::E_MOTOR_GEARSET_18, p_reversed);
  else
    m_intakeMotor = Motor::findMotor(p_intakeMotor);
  return 0;
}

int Intake::autonomous(){
  // Later :)
  return 0;
}

int Intake::driverControl(){
  m_intakeMotor->setVelocity(m_velocity);
  return 0;
}

int Intake::disabled(){
  m_intakeMotor->setVelocity(0);
  return 0;
}
