#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"
#include "robot/devices/externalFileClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/devices/taskScheduleClass.hpp"
#include "robot/graphical/GUIClass.hpp"
#include "robot/subsystems/armClass.hpp"
#include "robot/subsystems/intakeClass.hpp"
#include "robot/subsystems/baseClass.hpp"

#ifndef ROBOTCLASS_H
#define ROBOTCLASS_H

class Robot{
private:
  GraphicalInterface m_gui;
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

  RobotMode m_robotMode;

  int defineGUI();
  friend class Base;
  friend class Odometry;
public:
  Robot();

  int task();

  GraphicalInterface& getGUI();

  int driverControl();

  int autonmous();

  int disabled();

  TaskScheduler& getTaskScheduler();

  RobotMode getRobotMode();
};

#endif // ROBOTCLASS_H
