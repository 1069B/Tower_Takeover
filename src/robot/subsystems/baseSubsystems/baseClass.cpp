#include "robot/subsystems/baseClass.hpp"

Base::Base(BaseType p_baseType, BaseMode p_baseMode, bool p_trackingSystem, Controller& p_mainController, Controller& p_partnerController){
  m_baseType = p_baseType;
  m_baseMode = p_baseMode;
  m_trackingSystem = p_trackingSystem;
  m_mainController = &p_mainController;
  m_partnerController = &p_partnerController;
  m_mainController->Axis1.setMultiplier(2);
  m_mainController->Axis2.setMultiplier(2);
  m_mainController->Axis3.setMultiplier(2);
  m_mainController->Axis4.setMultiplier(2);
}

BaseType Base::getType(){
  return m_baseType;
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
