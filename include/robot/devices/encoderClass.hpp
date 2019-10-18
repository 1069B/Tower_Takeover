#include "robot/devices/timerClass.hpp"

#ifndef ENCODERCLASS_H
#define ENCODERCLASS_H

class Encoder{
private:
  std::string m_name = "Encoder";
  short m_port;// 1,3,5,7
  Timer m_timer;

  int m_zeroPosition = 0;
  int m_previousTime = 0;
  int m_previousPosition = 0;
  int m_rotation = 0;
  int m_velocity = 0;

public:
  Encoder(const std::string p_name ,const int p_port);

  bool isConnected();

  int getRotation();

  int resetRotation();

  int getVelocity();

  int defineGUI();

  int changePort(const short p_port);
};

#endif // ENCODERCLASS_H
