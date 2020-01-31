#include "robot/graphical/GUIClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/subsystems/baseClass.hpp"
#include "robot/subsystems/armClass.hpp"
#include "robot/subsystems/intakeClass.hpp"
#include "robot/devices/taskScheduleClass.hpp"
#include "robot/autonomousClass.hpp"

#ifndef ROBOTCLASS_H
#define ROBOTCLASS_H

class Robot{
private:
  graphicalInterface m_gui;
  Controller m_mainController;
  Controller m_partnerController;
  Timer m_timer;
  ExternalFile m_config;
  TaskScheduler m_taskScheduler;

  Base m_base;

  Arm m_tray;
  Arm m_slider;

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

  int driverControl();

  int autonmous();

  int disabled();

  TaskScheduler& getTaskScheduler();
};

#endif // ROBOTCLASS_H
