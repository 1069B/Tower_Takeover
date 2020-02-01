#include "robot/graphical/GUIClass.hpp"

#ifndef AUTONOMOUSCLASS_H
#define AUTONOMOUSCLASS_H

class Robot;

enum AutonomousSide{
  AUTO_BLUE = 0,
  AUTO_RED = 1,
  AUTO_SKILLS = 2,
  AUTO_NONE = 3
};

struct autoBaseEvent{
public:
  int m_actionDelay = 0;
  double m_desiredXPosition = 0;
  double m_desiredYPosition = 0;
  double m_desiredOrientation = 0;
  short m_maximumVelocity = 0;
  pros::motor_brake_mode_e m_endBrakeMode = pros::E_MOTOR_BRAKE_COAST;
};

struct autoArmEvent{
public:
  int m_actionDelay = 0;
  double m_desiredPosition = 0;
  short m_maximumVelocity = 0;
  pros::motor_brake_mode_e m_endBrakeMode = pros::E_MOTOR_BRAKE_COAST;
};

struct autoIntakeEvent{
public:
  int m_actionDelay = 0;
  int m_desiredDuration = 0;
  double m_desiredPosition = 0;
  short m_maximumVelocity = 0;
  bool m_duration = true;
  pros::motor_brake_mode_e m_endBrakeMode = pros::E_MOTOR_BRAKE_COAST;
};

class AutoProgram{
private:
  std::string m_name;
  AutonomousSide m_autoSide;
  int m_programNumber;

public:
  AutoProgram(const std::string p_name, const AutonomousSide p_autoSide, const int p_programNumber);

  std::string getName();

  AutonomousSide getAutoSide();

  int getProgramNumber();
};

class Autonomous{
private:
  Robot& m_robot;
  std::string m_name = "Autonomous";
  int m_selectedProgramNumber = INT_MAX;
  int m_autoSide = AUTO_NONE;

  std::vector<std::string> m_blueProgramNames;
  std::vector<AutoProgram*> m_bluePrograms;

  std::vector<std::string> m_redProgramNames;
  std::vector<AutoProgram*> m_redPrograms;

  std::vector<std::string> m_skillsProgramNames;
  std::vector<AutoProgram*> m_skillsPrograms;

  std::vector<std::string> m_displayProgramNames;

  int displayRedAuto();
  int displayBlueAuto();
  int displaySkillsAuto();

public:
  Autonomous(Robot& p_robot);

  int addProgram(AutoProgram& p_program);

  AutoProgram* findProgram(const int p_number, const AutonomousSide p_autoSide);

  int defineGUI(const std::string p_returnScreenID);

  int autoProgramDaemon();

  int task();

};

#endif // AUTONOMOUSCLASS_H
