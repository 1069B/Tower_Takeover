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
	TANK2 = 3,
	TANK4 = 4
};

enum BaseMode {
	NO_CORECTIONS = 0,
	ACTIVE_CORRECTIONS = 1,
};

class Base{
private:
  Motor* m_frontLeftMotor = NULL;
  Motor* m_frontRightMotor = NULL;
  Motor* m_backLeftMotor = NULL;
  Motor* m_backRightMotor = NULL;
  Motor* m_centerMotor = NULL;

  Encoder* m_leftEncoder = NULL;
  Encoder* m_centerEncoder = NULL;
  Encoder* m_rightEncoder = NULL;

  Controller* m_driveController = NULL;
  Controller* m_partnerController = NULL;

  ExternalFile* m_config;

  bool m_trackingSystem = true;
  BaseType m_baseType;
	BaseMode m_baseMode;

	int setVector();

	int setTarget();

public:
  Base(BaseType p_baseType, BaseMode p_baseMode, bool p_trackingSystem);

	BaseType getType();

	int defineHolonomic(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor);

	int defineHBase(std::string p_backLeftMotor, std::string p_backRightMotor, std::string p_centerMotor);

	int defineMecanum(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor);

	int defineTank2(std::string p_backLeftMotor, std::string p_backRightMotor);

	int defineTank4(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor);

	int initialize();

	int autonomous();

	int driverControl();


};

#endif // BASECLASS_H