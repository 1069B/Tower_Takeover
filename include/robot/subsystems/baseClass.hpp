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

  Controller* m_mainController = NULL;
  Controller* m_partnerController = NULL;

  ExternalFile* m_config;

  bool m_trackingSystem = false;
  BaseType m_baseType;
	BaseMode m_baseMode;

	int setVector();

	int setTarget();

	int initializeHolonomic(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor);
	int driverHolonomic();
	int autonomousHolonomic();

	int initializeHBase(std::string p_backLeftMotor, std::string p_backRightMotor, std::string p_centerMotor);
	int driverHBase();
	int autonomousHBase();

	int initializeMecanum(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor);
	int driverMecanum();
	int autonomousMecanum();

	int initializeTank2(std::string p_backLeftMotor, std::string p_backRightMotor);
	int driverTank2();
	int autonomousTank2();

	int initializeTank4(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor);
	int driverTank4();
	int autonomousTank4();

	int initializeTrackingSystem(std::string p_leftEncoder, std::string p_rightEncoder, std::string p_centerEncoder);

public:
  Base(BaseType p_baseType, BaseMode p_baseMode, bool p_trackingSystem, Controller& p_mainController, Controller& p_partnerController);

	BaseType getBaseType();
	BaseMode getBaseMode();

	int setBaseType();
	int setBaseMode();

	int initialize();
	int autonomous();
	int driverControl();

	int defineGUI(graphicalInterface& p_gui, const std::string p_returnScreen);
};

#endif // BASECLASS_H
