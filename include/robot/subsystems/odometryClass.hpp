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

  int m_orientation = 0;
  int m_xPosition = 0;
  int m_yPosition = 0;

  double m_trakingWheelDistance = 5.4;//Units in cm

  double getArcTuringRadius();

  double getOpposedTurningRadius();

public:
  Odometry(Robot& p_robot, const std::string p_leftEncoder, const std::string p_rightEncoder, const std::string p_centerEncoder);

  int getOrientation();

  int getOrientationChange();

  int getOrientationVelocity();

  double getRadius();

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
