// #include "robot/graphical/GUIClass.hpp"
//
// #ifndef AUTONOMOUSCLASS_H
// #define AUTONOMOUSCLASS_H
// //
// class Robot;
//
// enum AutonomousSide{
//   AUTO_BLUE = 0,
//   AUTO_RED = 1,
//   AUTO_SKILLS = 2
// };
//
// class AutoProgram{
// private:
//   std::string m_name;
//
// public:
//   AutoProgram(std::string p_name);
//
//   std::string getName();
// };
//
// class Autonomous{
// private:
//   Robot& m_robot;
//   std::vector<AutoProgram*> m_programs;
//
//   std::vector<std::string> m_blueProgramNames;
//   std::vector<std::string> m_redProgramNames;
//   std::vector<std::string> m_skillsProgramNames;
// public:
//   int m_selectedProgramNumber;
//
//   Autonomous(Robot& p_robot);
//
//   int addProgram(AutoProgram* p_program, const int m_programNumber);
//
//   AutoProgram* findProgram(const std::string p_name);
//
//   int defineGUI(const std::string p_returnScreenID);
//
//   int task();
//
// };
//
// #endif // AUTONOMOUSCLASS_H
