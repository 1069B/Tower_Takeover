#include "main.h"
#include "robot/devices/motorClass.hpp"
#include "robot/devices/encoderClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/graphical/GUIClass.hpp"

#ifndef BASECLASS_H
#define BASECLASS_H

enum BaseType {
	HOLONOMIC = 0,
	HBASE = 1,
	MECANUM = 2,
	TANK = 3
};

class Base{
protected:
  Motor* m_frontLeftMotor;
  Motor* m_frontRightMotor;
  Motor* m_backLeftMotor;
  Motor* m_backRightMotor;
  Motor* m_centerMotor;

  Encoder* m_leftEncoder;
  Encoder* m_centerEncoder;
  Encoder* m_rightEncoder;

  Controller* m_driveController;
  Controller* m_partnerController;

  ExternalFile* m_config;

  bool m_trackingSystem = true;
  BaseType m_baseType;
  
  Base();


};

#endif // BASECLASS_H
