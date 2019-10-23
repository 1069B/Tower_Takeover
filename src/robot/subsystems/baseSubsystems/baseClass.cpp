#include "robot/subsystems/baseClass.hpp"

Base::Base(BaseType p_baseType, BaseMode p_baseMode, bool p_trackingSystem, Controller& p_mainController, Controller& p_partnerController){
  m_baseType = p_baseType;
  m_baseMode = p_baseMode;
  m_trackingSystem = p_trackingSystem;
  m_mainController = &p_mainController;
  m_partnerController = &p_partnerController;
}

BaseType Base::getType(){
  return m_baseType;
}

int Base::defineHolonomic(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor){
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

int Base::defineHBase(std::string p_backLeftMotor, std::string p_backRightMotor, std::string p_centerMotor){
  if(Motor::findMotor(p_centerMotor) == NULL)
    m_centerMotor = new Motor(p_centerMotor, 1, pros::E_MOTOR_GEARSET_18, false);
  else
    m_centerMotor = Motor::findMotor(p_centerMotor);

  if(Motor::findMotor(p_backLeftMotor) == NULL)
    m_backLeftMotor = new Motor(p_backLeftMotor, 2, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backLeftMotor = Motor::findMotor(p_backLeftMotor);

  if(Motor::findMotor(p_backRightMotor) == NULL)
    m_backRightMotor = new Motor(p_backRightMotor, 3, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backRightMotor = Motor::findMotor(p_backRightMotor);
  return 0;
}

int Base::defineMecanum(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor){
  if(Motor::findMotor(p_frontLeftMotor) == NULL)
    m_frontLeftMotor = new Motor(p_frontLeftMotor, 1, pros::E_MOTOR_GEARSET_18, false);
  else
    m_frontLeftMotor = Motor::findMotor(p_frontLeftMotor);

  if(Motor::findMotor(p_frontRightMotor) == NULL)
    m_frontRightMotor = new Motor(p_frontRightMotor, 2, pros::E_MOTOR_GEARSET_18, false);
  else
    m_frontRightMotor = Motor::findMotor(p_frontRightMotor);

  if(Motor::findMotor(p_backLeftMotor) == NULL)
    m_backLeftMotor = new Motor(p_backLeftMotor, 3, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backLeftMotor = Motor::findMotor(p_backLeftMotor);

  if(Motor::findMotor(p_backRightMotor) == NULL)
    m_backRightMotor = new Motor(p_backRightMotor, 4, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backRightMotor = Motor::findMotor(p_backRightMotor);
  return 0;
}

int Base::defineTank2(std::string p_backLeftMotor, std::string p_backRightMotor){
  if(Motor::findMotor(p_backLeftMotor) == NULL)
    m_backLeftMotor = new Motor(p_backLeftMotor, 1, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backLeftMotor = Motor::findMotor(p_backLeftMotor);

  if(Motor::findMotor(p_backRightMotor) == NULL)
    m_backRightMotor = new Motor(p_backRightMotor, 2, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backRightMotor = Motor::findMotor(p_backRightMotor);
  return 0;
}

int Base::defineTank4(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor){
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

int Base::initialize(){
  return 0;
}

int Base::autonomous(){
  return 0;
}

int Base::driverControl(){
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
