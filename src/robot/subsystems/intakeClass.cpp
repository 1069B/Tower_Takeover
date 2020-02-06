#include "robot/subsystems/intakeClass.hpp"
#include "robot/devices/motorClass.hpp"
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
  m_velocity = abs(p_velocity);
  m_targetPosition = p_position;
  if(m_intakeMotor -> getRotation() < p_position)
    m_direction = 1;
  else if(m_intakeMotor -> getRotation() > p_position)
    m_direction = -1;
  else
    m_direction = 0;
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

int Intake::setBrake(const pros::motor_brake_mode_e_t p_brakeMode){
  m_intakeMotor->setBrake(p_brakeMode);
  m_brakeMode = p_brakeMode;
  return 0;
}

int Intake::autonomous(const double p_desiredPosition, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode){
  return 0;
}
int Intake::autonomous(const int m_desiredDuration, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode){
  return 0;
}

int Intake::task(){
  switch ((int)m_intakeState) {
    case (int)VELOCITY_DEPENDENT:
      m_intakeMotor->setVelocity(m_velocity);
      break;

    case (int)TIME_DEPENDENT:
      m_intakeMotor -> setVelocity(m_velocity);
      if(m_timer.preformAction()){
        m_intakeState = DISABLED;
      }
      break;

    case (int)ENCODER_DEPENDENT:
      switch (m_direction) {
        case 1:// Forwards
          m_intakeMotor->setVelocity(m_velocity);
          if(m_intakeMotor -> getRotation() >= m_targetPosition)
            m_intakeState = DISABLED;
          break;
        case 0:// NULL
          m_intakeState = DISABLED;
          break;
        case -1:// Backwards
          m_intakeMotor->setVelocity(-m_velocity);
          if(m_intakeMotor -> getRotation() <= m_targetPosition)
            m_intakeState = DISABLED;
          break;
      }
      break;

    case (int)DISABLED:
      m_intakeMotor -> setVelocity(0);
      break;
  }
  return 0;
}

int Intake::disable(){
  m_intakeState = DISABLED;
  return 0;
}
