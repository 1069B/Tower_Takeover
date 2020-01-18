#include "robot/devices/motorClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/graphical/GUIClass.hpp"

class Robot;

#ifndef ARMCLASS_H
#define ARMCLASS_H

enum ArmPosition{
  UP = 0,
  INTRANSIT = 1,
  DOWN = 2,
  NOPOSITION = 3
};

class Arm {
private:
  Robot& m_robot;
  Motor* m_armMotor;

  static ExternalFile m_config;
  Timer m_timer;
  manipulatorState m_armState = DISABLED;
  ArmPosition m_armPosition = DOWN;
  int m_velocity;
  int m_targetPosition;
  int m_direction;
  bool m_reversed;
  pros::motor_brake_mode_e_t m_brakeMode;

  int m_limitLow = 0;
  int m_limitHigh = 0;

  int logrithmicCurve();
public:
  Arm(Robot& p_robot);

  int setVelocity(const int p_velocity = 0);

  int setMovementDuration(const int p_velocity, const int p_duration);

  int moveToPosition(const int p_velocity, const int p_position);

  int setBrake(const pros::motor_brake_mode_e_t p_brakeMode);

  int setUp();

  int setDown();

  int resetEncoder();

  int initialize(const std::string p_armMotor, const int p_port, const int p_limitLow, const int p_limitHigh, const bool p_reversed = false);

  int task();
};

#endif // LIFTCLASS_H
