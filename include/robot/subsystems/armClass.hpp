#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"

class Robot;

#ifndef ARMCLASSV2_H
#define ARMCLASSV2_H

class Arm {
private:
  Robot& m_robot;
  Motor* m_armMotor;

  int m_startPosition = 0;
  int m_currentPosition = 0;
  int m_endPosition = 0;

  int m_movementDisplacement = 0;
  int m_movementDirection = 0;
  int m_movementMaximumVelocity = 0;

  bool m_movementInProgess = false;

  int m_desiredVelcoity = 0;

  int m_limitLow = 0;
  int m_limitHigh = 0;
  int m_totalPossibleDisplacement = 0;

  int m_velcoityMaximum = 200;
  double m_velocityMaximumCoefficent = 2;

  double m_speedUpPercent = .25;
  double m_speedUpSlope=0;
  double m_speedUpDisplacement = 0;

  double m_speedDownPercent = .25;
  double m_speedDownSlope=0;
  double m_speedDownDisplacement = 0;

  int m_preset1 = 0;
  int m_preset2 = 0;
  int m_preset3 = 0;
  int m_preset4 = 0;

  pros::motor_brake_mode_e m_brakeMode = pros::E_MOTOR_BRAKE_HOLD;

  bool m_reversed;
  ManipulatorMode m_mode = MANIPULATOR_DISABLED;


public:
  Arm(Robot& p_robot);

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

  int goToPosition(const int p_position, const double p_speedUpPercent, const double p_speedDownPercent, const int p_maximumVelocity);// Mode 1

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
