#include "main.h"
#include "robot/devices/encoderClass.hpp"

#ifndef ODOMETRYCLASS_H
#define ODOMETRYCLASS_H

class Robot;

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

	double m_radiusLeft = 0;
	double m_radiusRight = 0;
	double m_radiusAvg = 0;

	double m_orientationChange = 0;
	double m_velocityLeft = 0;
	double m_velocityRight = 0;
	double m_velocityAvg = 0;

  double m_timeChange = 0;

	double m_currentOrientationTime;
	double m_previousOrientationTime;

	double m_currentOrientationVelocityTime;
	double m_previousOrientationVelocityTime;
  
	double m_currentOrientation;
	double m_previousOrientation;

	Timer m_timer;

  std::string m_turnType;
	double m_trakingDistanceTotal = 26.355;//Units in cm
	double m_trackingDistanceLeft = 13.496;//Units in cm
	double m_trackingDistanceRight = 12.859;//Units in cm

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
