#include "main.h"
#include "robot/devices/encoderClass.hpp"

#ifndef ODOMETRYCLASS_H
#define ODOMETRYCLASS_H

class Robot;

enum TurnType {
	ARC = 0,
	POINT = 1,
	OPPOSED = 2,
  NOTURN = 3
};

class Odometry{
private:
  std::string m_name = "Odometry";
  Robot& m_robot;

  Encoder* m_leftEncoder = NULL;
  Encoder* m_centerEncoder = NULL;
  Encoder* m_rightEncoder = NULL;

  double m_orientation = 0;
  double m_xPosition = 0;
  double m_yPosition = 0;

	double m_leftRadius = 0;
	double m_rightRadius = 0;
	double m_averageRadius = 0;

	Timer m_timer;
	double m_currentOrientationTime;
	double m_previousOrientationTime;
	double m_currentOrientationVelocityTime;
	double m_previousOrientationVelocityTime;
	double m_currentOrientation;
	double m_previousOrientation;

  TurnType m_turnType;
  double m_trakingDistanceLeft = 13.496;//Units in cm
  double m_trakingDistanceRight = 12.859;//Units in cm

public:
  Odometry(Robot& p_robot, const std::string p_leftEncoder, const std::string p_rightEncoder, const std::string p_centerEncoder);

  double getOrientation();

  double getOrientationChange();

  double getOrientationVelocity();

  double getRadiusLeft(const double p_leftVelocity, const double p_rightVelocity);

  double getRadiusRight(const double p_leftVelocity, const double p_rightVelocity);

  double setOrientation(const double p_orientation);

  double getXposition();

  double getXVelocity();

  double setXposition(const double p_xPosition);

  double getYposistion();

  double getYVelocity();

  double setYposition(const double p_yPosition);

  int defineGUI(const std::string p_returnScreen);
};
#endif // ODOMETRYCLASS_H
