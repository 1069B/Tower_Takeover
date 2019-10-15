#include "robot/devices/timerClass.hpp"

#ifndef ENCODERCLASS_H
#define ENCODERCLASS_H

class Encoder{
private:
  std::string m_name = "Encoder";
  short m_port;// 1,3,5,7
  Timer m_timer;

  int m_zeroPosition;
  int m_previousTime = 0;
  int m_previousPosition = 0;
  int m_rotation;
  int m_velocity;

public:
  Encoder(const std::string p_name ,const int p_port);

  bool isConnected();

  int getRotation();

  int resetRotation();

  int getVelocity();

  int defineGUI();
};

#endif // ENCODERCLASS_H
