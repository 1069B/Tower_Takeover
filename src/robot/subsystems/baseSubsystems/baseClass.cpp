#include "robot/subsystems/baseClass.hpp"
#include "robotClass.hpp"

Base::Base(Robot& p_robot, BaseType p_baseType, BaseMode p_baseMode, bool p_trackingSystem):
m_robot(p_robot), m_config("Base_Config.txt")
{
  if(m_config.varExist("Base_Type"))
    m_baseType = (BaseType)m_config.readInt("Base_Type");
  else
    m_baseType = p_baseType;

  m_baseMode = p_baseMode;
  m_trackingSystem = p_trackingSystem;
  m_robot.m_mainController.Axis1.setMultiplier(2);
  m_robot.m_mainController.Axis2.setMultiplier(2);
  m_robot.m_mainController.Axis3.setMultiplier(-2);
  m_robot.m_mainController.Axis4.setMultiplier(2);

  m_speedUpCurve = true;
  m_driftTurning = true;
}

BaseType Base::getBaseType(){
  return m_baseType;
}

bool Base::getTrackingSystem(){
  return m_trackingSystem;
}

double Base::speedUp(int p_controllerValue){
  double l_a = m_speedUpA;
	double l_b = m_speedUpB;
	double l_c = m_speedUpC;
	double l_h = m_speedUpH;
  if(p_controllerValue != 0){
    if(p_controllerValue > 5){
      return l_a/(1+(l_a - l_b)/l_b * pow(M_E, (-l_c*(p_controllerValue + l_h))));
    }
    else if(p_controllerValue < -5){
      return -l_a/(1+(l_a - l_b)/l_b * pow(M_E, (l_c*(p_controllerValue - l_h))));
    }
    else
      return 0;
  }
  return 0 ;
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

  if(m_trackingSystem)
    m_trackingWheels = new Odometry(m_robot, "BaseLeft", "BaseRight", "BaseCenter");

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

  if(m_trackingSystem)
    m_trackingWheels->getOrientation();
  return 0;
}

int Base::disabled(){
  switch((int)m_baseType) {
    case HOLONOMIC:
      disabledHolonomic();
      break;

    case HBASE:
      disabledHBase();
      break;

    case MECANUM:
      disabledMecanum();
      break;

    case TANK2:
      disabledTank2();
      break;

    case TANK4:
      disabledTank4();
      break;
  }

  return 0;
}

int Base::defineGUI(std::string p_returnScreen){
  if(m_trackingSystem)
    m_trackingWheels->defineGUI(p_returnScreen);
  return 0;
}
