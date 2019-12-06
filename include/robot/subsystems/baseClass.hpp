#include "main.h"
#include "robot/devices/motorClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/graphical/GUIClass.hpp"
#include "robot/subsystems/odometryClass.hpp"

#ifndef BASECLASS_H
#define BASECLASS_H

class Robot;

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
	//General Varibles
	Robot& m_robot;

  Motor* m_frontLeftMotor = NULL;
  Motor* m_frontRightMotor = NULL;
  Motor* m_backLeftMotor = NULL;
  Motor* m_backRightMotor = NULL;
  Motor* m_centerMotor = NULL;

	Odometry* m_trackingWheels= NULL;

  ExternalFile m_config;

  bool m_trackingSystem = false;
	bool m_speedUpCurve = false;
	BaseType m_baseType;
	BaseMode m_baseMode;

	int m_frontLeftVelocity = 0;
  int m_frontRightVelocity = 0;
  int m_backLeftVelocity = 0;
  int m_backRightVelocity = 0;
  int m_centerVelocity = 0;

	//Holonomic Varibles
	bool m_driftTurning = false;

	//Speed-Up Varibles
	int m_speedUpA = 201;
	int m_speedUpB = 5;
	double m_speedUpC = 0.05;
	int m_speedUpH = -27;

	friend class Robot;

	int setVector();

	int setTarget();

	int initializeHolonomic(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor);
	int driverHolonomic();
	int autonomousHolonomic();
	int disabledHolonomic();

	int initializeHBase(std::string p_backLeftMotor, std::string p_backRightMotor, std::string p_centerMotor);
	int driverHBase();
	int autonomousHBase();
	int disabledHBase();

	int initializeMecanum(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor);
	int driverMecanum();
	int autonomousMecanum();
	int disabledMecanum();

	int initializeTank2(std::string p_backLeftMotor, std::string p_backRightMotor);
	int driverTank2();
	int autonomousTank2();
	int disabledTank2();

	int initializeTank4(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor);
	int driverTank4();
	int autonomousTank4();
	int disabledTank4();

	double speedUp(int p_controllerValue);
public:
  Base(Robot& p_robot, BaseType p_baseType, BaseMode p_baseMode, bool p_trackingSystem);

	BaseType getBaseType();
	BaseMode getBaseMode();

	int setBaseType(BaseType p_baseType);
	int setBaseMode(BaseMode p_baseMode);

	bool getTrackingSystem();

	int initialize();
	int autonomous();
	int driverControl();
	int disabled();

	int defineGUI(std::string p_returnScreen);
};

#endif // BASECLASS_H
