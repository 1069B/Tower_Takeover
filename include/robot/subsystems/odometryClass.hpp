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
  int m_currentX = 0;
  int m_currentY = 0;
public:
  Odometry(Robot& p_robot, std::string p_leftEncoder, std::string p_rightEncoder, std::string p_centerEncoder);

  int getOrientation();

  int getOrientationVelocity();

  int setOrientation(int p_orientation);

  int getXposition();

  int getXVelocity();

  int setXposition();

  int getYposistion();

  int getYVelocity();

  int setYposition();

  int defineGUI(std::string p_returnScreen);
};
#endif // ODOMETRYCLASS_H
