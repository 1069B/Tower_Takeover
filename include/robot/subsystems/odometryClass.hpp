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

  int m_orientation = 0;
  int m_xPosition = 0;
  int m_yPosition = 0;

	Timer m_timer;
	int m_currentOrientationTime;
	int m_previousOrientationTime;
	int m_currentOrientationVelocityTime;
	int m_previousOrientationVelocityTime;
	double m_currentOrientation;
	double m_previousOrientation;

  TurnType m_turnType;
  double m_trakingDistanceLeft = 13.496;//Units in cm
  double m_trakingDistanceRight = 12.859;//Units in cm

public:
  Odometry(Robot& p_robot, const std::string p_leftEncoder, const std::string p_rightEncoder, const std::string p_centerEncoder);

  int getOrientation();

  int getOrientationChange();

  int getOrientationVelocity();

  double getRadiusLeft(const double p_leftVelocity, const double p_rightVelocity);

  double getRadiusRight(const double p_leftVelocity, const double p_rightVelocity);

  int setOrientation(const int p_orientation);

  int getXposition();

  int getXVelocity();

  int setXposition(const int p_xPosition);

  int getYposistion();

  int getYVelocity();

  int setYposition(const int p_yPosition);

  int defineGUI(const std::string p_returnScreen);
};
#endif // ODOMETRYCLASS_H
