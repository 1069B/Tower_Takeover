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
  switch((int)m_baseType) {
    case HOLONOMIC:
      initializeHolonomic("BaseFrontLeft", "BaseFrontRight" , "BaseBackLeft", "BaseBackRight");
      break;

    case HBASE:
      initializeHBase("BaseBackLeft", "BaseBackRight", "BaseCenter");
      break;

    case MECANUM:
      initializeMecanum("BaseFrontLeft", "BaseFrontRight" , "BaseBackLeft", "BaseBackRight");
      break;

    case TANK2:
      initializeTank2("BaseBackLeft", "BaseBackRight");
      break;

    case TANK4:
      initializeTank4("BaseFrontLeft", "BaseFrontRight" , "BaseBackLeft", "BaseBackRight");
      break;
  }
  return 0;
}

int Base::autonomous(){
  switch((int)m_baseType) {
    case HOLONOMIC:
      autonomousHolonomic();
      break;

    case HBASE:
      autonomousHBase();
      break;

    case MECANUM:
      autonomousMecanum();
      break;

    case TANK2:
      autonomousTank2();
      break;

    case TANK4:
      autonomousTank4();
      break;
  }
  return 0;
}

int Base::driverControl(){
  switch((int)m_baseType) {
    case HOLONOMIC:
      driverHolonomic();
      break;

    case HBASE:
      driverHBase();
      break;

    case MECANUM:
      driverMecanum();
      break;

    case TANK2:
      driverTank2();
      break;

    case TANK4:
      driverTank4();
      break;
  }
  return 0;
}
