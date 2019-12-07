#include "main.h"
#include "robot/graphical/GUIClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/subsystems/baseClass.hpp"
#include "robot/subsystems/armClass.hpp"
#include "robot/subsystems/intakeClass.hpp"

#ifndef ROBOTCLASS_H
#define ROBOTCLASS_H

class Robot{
private:
  graphicalInterface m_gui;
  Controller m_mainController;
  Controller m_partnerController;
  Timer m_timer;
  ExternalFile m_config;
  Base m_base;

  Arm m_tray;
  Arm m_intakeArm;

  Intake m_leftIntake;
  Intake m_rightIntake;

  std::string m_compMode;

  int defineGUI();
  friend class Base;
  friend class Odometry;
public:
  Robot();

  int task();

  graphicalInterface& getGUI();

  int autonmous();

  int disabled();
};

#endif // ROBOTCLASS_H
