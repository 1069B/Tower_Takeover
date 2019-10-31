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
  bool m_reversed = false;

  static ExternalFile s_config;
  static std::vector<Encoder*> s_encoderArray;

public:
  Encoder(const std::string p_name, const int p_port, const bool p_reverse);

  int isConnected();// Still need a methoud for detecting connection

  int getRotation();

  std::string getName();

  int resetRotation();

  int getVelocity();

  int setPort(const int p_port);

  int setReverse(const bool p_reverse);

  int defineGUI(graphicalInterface& p_gui, const std::string p_returnScreen);

  static Encoder* findEncoder(const std::string p_name);

  static Encoder* findEncoder(const short p_port);
};

#endif // ENCODERCLASS_H
