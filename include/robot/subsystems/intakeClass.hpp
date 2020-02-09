#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"
#include "robot/devices/externalFileClass.hpp"

#ifndef INTAKECLASS_H
#define INTAKECLASS_H

class Intake{
private:
  Robot& m_robot;
  Motor* m_intakeMotor = NULL;
  static ExternalFile m_config;
  Timer m_timer;
  ManipulatorMode m_intakeState = MANIPULATOR_VELOCITY_DEPENDENT;
  pros::motor_brake_mode_e_t m_brakeMode = MOTOR_BRAKE_COAST;
  int m_velocity;
  int m_targetPosition;
  bool m_reversed;
  int m_direction = 0;

public:
  Intake(Robot& p_robot);

  int setVelocity(const int p_velocity = 0);

  int setMovementDuration(const int p_velocity, const int p_duration);

  int moveToPosition(const int p_velocity, const int p_position);

  int setBrake(const pros::motor_brake_mode_e_t p_brakeMode);

  int resetEncoder();

  int initialize(const std::string p_intakeMotor, const int p_port, const bool p_reversed = false);

	int autonomous(const double p_desiredPosition, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode);
  int autonomous(const int m_desiredDuration, const short p_maximumVelocity, const pros::motor_brake_mode_e p_endBrakeMode);

  int task();

  int disable();
};

#endif // INTAKECLASS_H
