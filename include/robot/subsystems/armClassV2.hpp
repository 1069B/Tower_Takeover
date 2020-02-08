#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"

class Robot;

#ifndef ARMCLASSV2_H
#define ARMCLASSV2_H

class ArmV2 {
private:
  Robot& m_robot;
  Motor* m_armMotor;

  int m_currentPosition = 0;
  int m_currentVelocity = 0;

  int m_desiredPosition = 0;
  int m_desiredVelcoity = 0;

  int m_limitLow = 0;
  int m_limitHigh = 0;
  int m_velcoityMaximum = 200;

  int m_preset1 = 0;
  int m_preset2 = 0;
  int m_preset3 = 0;
  int m_preset4 = 0;

  int m_accelerationCurveCoefficient = 1;

  pros::motor_brake_mode_e m_brakeMode = pros::E_MOTOR_BRAKE_HOLD;

  bool m_reversed;
  ManipulatorMode m_mode = MANIPULATOR_DISABLED;


public:
  ArmV2(Robot& p_robot);

  /* Setting Functions */
  int initialize(const std::string p_armMotor, const int p_port, const int p_limitLow, const int p_limitHigh, const bool p_reversed = false);

  int setLimitLow(const int p_limitLow);

  int setLimitHigh(const int p_limitHigh);

  int setPreset1(const int p_preset1);

  int setPreset2(const int p_preset2);

  int setPreset3(const int p_preset3);

  int setPreset4(const int p_preset4);

  int setAccelerationCurveCoefficent(const int p_coefficeint);

  int setBrake(const pros::motor_brake_mode_e p_brakeMode);

  int setMaximumVelcoity(const int p_velocityMax);

  /* GO TO FUNCTION */
  int goToVelocity(const int p_velocity);//Mode 0

  int goToPosition(const int p_position);// Mode 1

  int goToLimitLow();// Mode 2

  int goToLimitHigh();// Mode 3

  int goToPreset1();// Mode 4

  int goToPreset2();// Mode 5

  int goToPreset3();// Mode 6

  int goToPreset4();// Mode 7

  /* Main Task */

  int task();
};

#endif // ARMCLASSV2_H
