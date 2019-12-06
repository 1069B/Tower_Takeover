#include "main.h"
#include "robot/devices/motorClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/graphical/GUIClass.hpp"

class Robot;

#ifndef ARMCLASS_H
#define ARMCLASS_H

class Arm {
private:
  Robot& m_robot;
  Motor* m_armMotor;

  static ExternalFile m_config;
  Timer m_timer;
  manipulatorState m_armState = VELOCITY_DEPENDENT;
  int m_velocity;
  int m_targetPosition;
  bool m_reversed;

  int m_limitLow = 0;
  int m_limitHigh = 0;

public:
  Arm(Robot& p_robot);

  int setVelocity(const int p_velocity = 0);

  int setMovementDuration(const int p_velocity, const int p_duration);

  int moveToPosition(const int p_velocity, const int p_position);

  int resetEncoder();

  int initialize(const std::string p_armMotor, const int p_port, const int p_limitLow, const int p_limitHigh, const bool p_reversed = false);

  int autonomous();

  int driverControl();

  int disabled();
};

#endif // LIFTCLASS_H
