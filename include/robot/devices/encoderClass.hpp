#include "robot/devices/timerClass.hpp"
#include "robot/graphical/GUIClass.hpp"

#ifndef ENCODERCLASS_H
#define ENCODERCLASS_H

class RedEncoder{
private:
  std::string m_name = "Encoder";
  short m_port;// 1,3,5,7
  Timer m_timer;

  int m_zeroPosition = 0;
  int m_previousTime = 0;
  int m_previousRotation = 0;
  int m_rotation = 0;
  int m_velocity = 0;

public:
  RedEncoder(const std::string p_name ,const int p_port);

  bool isConnected();

  int getRotation();

  int resetRotation();

  int getVelocity();

  int defineGUI();

  int changePort(const short p_port);

  int defineGUI(graphicalInterface& p_gui, std::string p_returnScreen);
};

#endif // ENCODERCLASS_H
