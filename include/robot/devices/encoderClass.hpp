#include "robot/devices/timerClass.hpp"
#include "robot/graphical/GUIClass.hpp"

#ifndef ENCODERCLASS_H
#define ENCODERCLASS_H

class Encoder{
private:
  std::string m_name = "Encoder";
  short m_port;// 1,3,5,7
  Timer m_timer;

  int m_zeroPosition = 0;
  int m_previousTime = 0;
  int m_previousRotation = 0;
  int m_rotation = 0;
  int m_velocity = 0;

  static ExternalFile s_config;
  static std::vector<Encoder*> s_encoderArray;

public:
  Encoder(const std::string p_name ,const int p_port);

  bool isConnected();// Still need a methoud for detecting connection

  int getRotation();

  int resetRotation();

  int getVelocity();

  int changePort(const short p_port);

  int defineGUI(graphicalInterface& p_gui, std::string p_returnScreen);

  static Encoder* findEncoder(std::string p_name);
};

#endif // ENCODERCLASS_H
