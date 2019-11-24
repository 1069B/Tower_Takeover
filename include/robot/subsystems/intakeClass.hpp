#include "main.h"
#include "robot/devices/motorClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/graphical/GUIClass.hpp"

class Robot;

#ifndef INTAKECLASS_H
#define INTAKECLASS_H

enum IntakeState {
	VELOCITY_DEPENDENT = 0,
	TIME_DEPENDENT = 1,
	ENCODER_DEPENDENT = 2,
};

class Intake{
private:
  Robot& m_robot;
  Motor* m_intakeMotor = NULL;
  static ExternalFile m_config;
  Timer m_timer;
  IntakeState m_intakeState = VELOCITY_DEPENDENT;
  int m_velocity;
  int m_targetPosition;
  bool m_reversed;


  int setVelocity(const int p_velocity = 200);

  int setMovementDuration(const int p_velocity, const int p_duration);

  int moveToPosition(const int p_velocity, const int p_position);

  int resetEncoder();
public:
  Intake(Robot& p_robot);

  int initialize(const std::string p_intakeMotor, const int p_port, const bool p_reversed = false);

	int autonomous();

	int driverControl();
};

#endif // INTAKECLASS_H
