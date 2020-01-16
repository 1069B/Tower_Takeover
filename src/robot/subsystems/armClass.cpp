#include "robot/subsystems/armClass.hpp"
#include "robotClass.hpp"

Arm::Arm(Robot& p_robot) : m_robot(p_robot){

}
ExternalFile Arm::m_config("Arm_Config.txt");

int Arm::setVelocity(const int p_velocity){
  m_velocity = p_velocity;
  m_armState = VELOCITY_DEPENDENT;
  return 0;
}

int Arm::setMovementDuration(const int p_velocity, const int p_duration){
  m_velocity = p_velocity;
  m_armState = TIME_DEPENDENT;
  m_timer.addActionDelay(p_duration);
  return 0;
}

int Arm::moveToPosition(const int p_velocity, const int p_position){
  m_velocity = abs(p_velocity);
  m_targetPosition = p_position;
  if(m_armMotor -> getRotation() < p_position)
    m_direction = 1;
  else if(m_armMotor -> getRotation() > p_position)
    m_direction = -1;
  else
    m_direction = 0;
  m_armState = ENCODER_DEPENDENT;
  return 0;
}

int Arm::resetEncoder(){
  m_armMotor->resetRotation();
  return 0;
}

int Arm::initialize(const std::string p_armMotor, const int p_port, const int p_limitLow, const int p_limitHigh, const bool p_reversed){
  m_reversed = p_reversed;
  m_limitLow = p_limitLow;
  m_limitHigh = p_limitHigh;
  if(Motor::findMotor(p_armMotor) == NULL)
    m_armMotor = new Motor(p_armMotor,p_port,pros::E_MOTOR_GEARSET_36, p_reversed);
   else
     m_armMotor = Motor::findMotor(p_armMotor);

  m_armMotor->setBrake(pros::E_MOTOR_BRAKE_HOLD);

  m_armMotor->defineGUI(m_robot.getGUI(), "Home");

  return 0;
}

int Arm::setBrake(const pros::motor_brake_mode_e_t p_brakeMode){
  m_brakeMode = p_brakeMode;
  m_armMotor->setBrake(pros::E_MOTOR_BRAKE_HOLD);
  return 0;
}

int Arm::task(){
  switch ((int)m_armState) {
    case (int)VELOCITY_DEPENDENT:
      if(m_armMotor->getRotation() <= m_limitLow && m_velocity/abs(m_velocity) == -1)
        m_velocity = 0;
      else if(m_armMotor->getRotation() >= m_limitHigh && m_velocity/abs(m_velocity) == 1)
        m_velocity = 0;
      m_armMotor->setVelocity(m_velocity);
      break;

    case (int)TIME_DEPENDENT:
      m_armMotor -> setVelocity(m_velocity);
      if(m_timer.preformAction()){
        m_armState = DISABLED;
      }
      break;

    case (int)ENCODER_DEPENDENT:
      switch (m_direction) {
        case 1:// Forwards
          m_armMotor->setVelocity(m_velocity);
          if(m_armMotor -> getRotation() >= m_targetPosition)
            m_armState = DISABLED;
          break;
        case 0:// NULL
          m_armState = DISABLED;
          break;
        case -1:// Backwards
          m_armMotor->setVelocity(-m_velocity);
          if(m_armMotor -> getRotation() <= m_targetPosition)
            m_armState = DISABLED;
          break;
      }
      break;

    case (int)DISABLED:
      m_armMotor -> setVelocity(0);
      break;
  }
  return 0;
}
