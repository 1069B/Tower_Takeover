#include "main.h"
#include "robot/graphical/GUIClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/devices/motorClass.hpp"
#include "robot/devices/timerClass.hpp"
#include "robot/devices/externalFileClass.hpp"
#include "robot/devices/encoderClass.hpp"

#ifndef ROBOTCLASS_H
#define ROBOTCLASS_H

class Robot{
private:
  graphicalInterface m_gui;
  Controller m_mainController;
  Controller m_partnerController;
  Timer m_timer;
  ExternalFile m_config;

  std::string m_compMode;
  std::string m_baseType;
  RedEncoder Enc1;

  int defineGUI();
public:
  Robot();

  int task();
};

#endif // ROBOTCLASS_H
