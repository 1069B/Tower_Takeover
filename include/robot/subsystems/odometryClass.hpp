#include "main.h"
#include "robot/devices/encoderClass.hpp"

#ifndef ODOMETRYCLASS_H
#define ODOMETRYCLASS_H

class Odometry{
private:
  Encoder* m_leftEncoder = NULL;
  Encoder* m_centerEncoder = NULL;
  Encoder* m_rightEncoder = NULL;
public:
  Odometry(std::string p_leftEncoder, std::string p_rightEncoder, std::string p_centerEncoder);
};
#endif // ODOMETRYCLASS_H
