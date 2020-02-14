#include "robot/varibleDecleration.hpp"
#include "robot/devices/externalFileClass.hpp"

#ifndef BASECLASSV2_H
#define BASECLASSV2_H

class BaseV2{
private:
  /*Basic Varibles*/
  std::string m_name = "Base";
  Robot m_robot;

  BaseState m_baseState = BASE_STATIONARY;

  int m_maximumVelocity = 200;
  /*Brake Varibles*/
  pros::motor_brake_mode_e m_brakeMode = pros::E_MOTOR_BRAKE_COAST;
  std::string m_brakeString = "Coast";

  /*Varibles for Automation*/
  Odometry m_odometry;

  double m_desriedOrientation;
  double m_desiredXPosition;
  double m_desiredYPosition;

  ExternalFile m_config;

public:
  BaseV2(Robot &p_robot, const int p_maximumVelocity);

  double setMaximumVelocity(int p_maximumVelocity);

  double setBrakeMode(pros::motor_brake_mode_e p_brakeMode);

  int goToPosition(const double p_xPosition, const double p_yPosition, const double p_speedUpPercent, const double p_speedDownPercent, const int p_intialVelocity, const int p_maximumVelocity);

  int goToVector(const double p_xVelocity, const double p_yVelocity);

  int superTask();
};

#endif // BASECLASSV2_H
