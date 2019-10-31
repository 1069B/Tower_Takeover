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
  int m_orientation;
  int m_currentX;
  int m_currentY;
  int m_targetX;
  int m_targetY;
  std::string m_actionName;
public:
  Odometry(Robot& p_robot, std::string p_leftEncoder, std::string p_rightEncoder, std::string p_centerEncoder);

  int defineGUI(std::string p_returnScreen);
};
#endif // ODOMETRYCLASS_H
