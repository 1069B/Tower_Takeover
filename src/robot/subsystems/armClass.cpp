#include "robot/subsystems/armClass.hpp"
#include "robot/devices/motorClass.hpp"
#include "robotClass.hpp"
#include "robot/graphical/components/alertClass.hpp"

Arm::Arm(Robot& p_robot) : m_robot(p_robot){

}

int Arm::initialize(const std::string p_armMotor, const int p_port, const int p_limitLow, const int p_limitHigh, const bool p_reversed){
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

int Arm::setLimitLow(const int p_limitLow){
  m_limitLow = p_limitLow;
  m_totalPossibleDisplacement = m_limitHigh - m_limitLow;
  return 0;
}

int Arm::setLimitHigh(const int p_limitHigh){
  m_limitHigh = p_limitHigh;
  m_totalPossibleDisplacement = m_limitHigh - m_limitLow;
  return 0;
}

int Arm::setPreset1(const int p_preset1){
  m_preset1 = p_preset1;
  return 0;
}

int Arm::setPreset2(const int p_preset2){
  m_preset2 = p_preset2;
  return 0;
}

int Arm::setPreset3(const int p_preset3){
  m_preset3 = p_preset3;
  return 0;
}

int Arm::setPreset4(const int p_preset4){
  m_preset4 = p_preset4;
  return 0;
}

int Arm::setAccelerationCurveCoefficent(const int p_coefficeint){
  //m_accelerationCurveCoefficient = p_coefficeint;
  return 0;
}

int Arm::setBrake(const pros::motor_brake_mode_e p_brakeMode){
  m_brakeMode = p_brakeMode;
  return 0;
}

int Arm::setMaximumVelcoity(const int p_velocityMax){
  m_velcoityMaximum = p_velocityMax;
  return 0;
}

/* GO TO FUNCTION */
int Arm::goToVelocity(const int p_velocity){
  m_mode = MANIPULATOR_VELOCITY_DEPENDENT;
  int l_direction = 0;
  if(p_velocity !=0)
    l_direction = (double)abs(p_velocity)/(double)p_velocity;

  if(abs(p_velocity) > m_velcoityMaximum)
    m_desiredVelcoity = m_velcoityMaximum * l_direction;
  else
    m_desiredVelcoity = p_velocity;
  return 0;
}

int Arm::goToPosition(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_maximumVelocity){
  m_mode = MANIPULATOR_ENCODER_DEPENDENT;
  m_speedUpPercent = p_speedUpPercent;
  m_speedDownPercent = p_speedDownPercent;
  m_velcoityMaximum = p_maximumVelocity;


  if(p_position > m_limitHigh){
    m_endPosition = p_position;
  }
  else if(p_position < m_limitLow){
    m_endPosition = p_position;
  }

  /*Set Varibles*/
  m_startPosition = m_armMotor->getRotation();
  m_movementDisplacement = m_endPosition-m_startPosition;

  /*Calculate Direction*/
  if(m_movementDisplacement != 0)
    m_movementDirection = m_movementDisplacement/abs(m_movementDisplacement);
  else
    m_movementDirection = 0;

  /*Calculate Safe Movement Maximum Velocity*/
  m_movementMaximumVelocity = m_velcoityMaximum * m_velocityMaximumCoefficent * ((double)m_movementDisplacement/(double)m_totalPossibleDisplacement);
  if(abs(m_movementMaximumVelocity) > m_velcoityMaximum)
    m_movementMaximumVelocity = m_velcoityMaximum;

  /*Calculate Speed Up Varibles*/
  m_speedUpDisplacement = m_movementDisplacement*m_speedUpPercent;
  m_speedUpSlope = (log((((double)m_movementMaximumVelocity + 1)/m_movementMaximumVelocity)-1))/(m_speedUpDisplacement - (m_speedUpDisplacement/2));

  /*Calculate Spped Down Varibles*/
  m_speedDownDisplacement = m_movementDisplacement * m_speedDownPercent;
  m_speedDownSlope = (log((((double)m_movementMaximumVelocity + 1)/m_movementMaximumVelocity)-1))/(m_speedDownDisplacement - (m_speedDownDisplacement/2));

  return 0;
}

int Arm::goToLimitLow(){
  goToPosition(m_limitLow, 0.25, 0.40, 75);
  return 0;
}

int Arm::goToLimitHigh(){
  goToPosition(m_limitHigh, 0.25, 0.40, 75);
  return 0;
}

int Arm::goToPreset1(){
  //goToPosition(m_preset1);
  return 0;
}

int Arm::goToPreset2(){
  //goToPosition(m_preset2);
  return 0;
}

int Arm::goToPreset3(){
  //goToPosition(m_preset3);
  return 0;
}

int Arm::goToPreset4(){
  //goToPosition(m_preset4);
  return 0;
}

int Arm::task(){
  m_currentPosition = m_armMotor->getRotation();

  if(m_robot.getRobotMode() == ROBOT_DISABLED){
    m_armMotor->setVelocity(0);
    m_armMotor->setBrake(m_brakeMode);
  }
  else if(m_robot.getRobotMode() == ROBOT_OPERATER || m_robot.getRobotMode() == ROBOT_AUTO){
    if(m_mode == MANIPULATOR_VELOCITY_DEPENDENT){
      if(m_armMotor->getRotation() <= m_limitLow && m_desiredVelcoity/abs(m_desiredVelcoity) == -1)
        m_desiredVelcoity = 0;
      else if(m_armMotor->getRotation() >= m_limitHigh && m_desiredVelcoity/abs(m_desiredVelcoity) == 1)
        m_desiredVelcoity = 0;
      m_armMotor->setVelocity(m_desiredVelcoity);
      m_armMotor->setBrake(m_brakeMode);
    }
    else if(m_mode == MANIPULATOR_ENCODER_DEPENDENT){
      if(abs(m_currentPosition-m_startPosition) < m_speedUpDisplacement){// Withen Speed Up
        int l_velocity = (m_movementMaximumVelocity + 1)/(1 + pow(M_E,(m_speedUpSlope*(m_currentPosition-((double)m_speedUpDisplacement/2.0)))));
        m_armMotor->setVelocity(l_velocity * m_movementDirection);
        g_alert.draw("Speed Up & Vel: " + std::to_string(l_velocity));
      }
      else if(abs(m_endPosition-m_currentPosition) < m_speedDownDisplacement){// Withen Slow Down
        int l_velocity = (m_movementMaximumVelocity + 1)/(1 + pow(M_E,(m_speedDownSlope*((m_endPosition-m_currentPosition)-((double)m_speedUpDisplacement/2.0)))));
        m_armMotor->setVelocity(l_velocity * m_movementDirection);
        g_alert.draw("Speed Down & Vel: " + std::to_string(l_velocity));
      }
      else{// Coast
        m_armMotor->setVelocity(m_movementMaximumVelocity * m_movementDirection);
        g_alert.draw("Coast & Vel: " + std::to_string(m_movementMaximumVelocity));
      }

      if((m_movementDirection == 1 && m_endPosition-m_currentPosition <= 0) || (m_movementDirection == -1 && m_endPosition-m_currentPosition >= 0)){
        m_armMotor->setVelocity(0);
        g_alert.draw("Done Up & Vel: " + std::to_string(0));
      }
      m_armMotor->setBrake(m_brakeMode);
    }
  }

  return 0;
}
