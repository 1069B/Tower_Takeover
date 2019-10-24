#include "robot/subsystems/baseClass.hpp"

int Base::initializeHolonomic(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor){
  if(Motor::findMotor(p_frontLeftMotor) == NULL)
    m_frontLeftMotor = new Motor(p_frontLeftMotor, 1, pros::E_MOTOR_GEARSET_18, false);
  else
    m_frontLeftMotor = Motor::findMotor(p_frontLeftMotor);

  if(Motor::findMotor(p_frontRightMotor) == NULL)
    m_frontRightMotor = new Motor(p_frontRightMotor, 2, pros::E_MOTOR_GEARSET_18, true);
  else
    m_frontRightMotor = Motor::findMotor(p_frontRightMotor);

  if(Motor::findMotor(p_backLeftMotor) == NULL)
    m_backLeftMotor = new Motor(p_backLeftMotor, 3, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backLeftMotor = Motor::findMotor(p_backLeftMotor);

  if(Motor::findMotor(p_backRightMotor) == NULL)
    m_backRightMotor = new Motor(p_backRightMotor, 4, pros::E_MOTOR_GEARSET_18, true);
  else
    m_backRightMotor = Motor::findMotor(p_backRightMotor);
  return 0;
}

int Base::autonomousHolonomic(){
  return 0;
}

int Base::driverHolonomic(){
  if((m_mainController->Axis1.getValue()) > 10 || (m_mainController->Axis1.getValue()) < -10){
    m_frontRightMotor->setVelocity(-m_mainController->Axis1.getValue());
    m_frontLeftMotor->setVelocity(m_mainController->Axis1.getValue());
    m_backRightMotor->setVelocity(-m_mainController->Axis1.getValue());
    m_backLeftMotor->setVelocity(m_mainController->Axis1.getValue());
  }
  else {
    m_frontRightMotor->setVelocity(m_mainController->Axis3.getValue()-m_mainController->Axis4.getValue());
    m_frontLeftMotor->setVelocity(m_mainController->Axis3.getValue()+m_mainController->Axis4.getValue());
    m_backRightMotor->setVelocity(m_mainController->Axis3.getValue()+m_mainController->Axis4.getValue());
    m_backLeftMotor->setVelocity(m_mainController->Axis3.getValue()-m_mainController->Axis4.getValue());
  }
  return 0;
}
