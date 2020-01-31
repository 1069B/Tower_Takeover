#include "robotClass.hpp"

AutoProgram::AutoProgram(const std::string p_name, const AutonomousSide p_autoSide, const int p_programNumber){
  m_name = p_name;
  m_autoSide = p_autoSide;
  m_programNumber = p_programNumber;
}

std::string AutoProgram::getName(){
  return m_name;
}

Autonomous::Autonomous(Robot& p_robot):m_robot(p_robot){
  m_blueProgramNames.resize(4);
  m_redProgramNames.resize(4);
  m_skillsProgramNames.resize(4);
  for(int x = 0; x < 4; x++){
    m_blueProgramNames.at(0) = "Not Defined";
    m_redProgramNames.at(0) = "Not Defined";
    m_skillsProgramNames.at(0) = "Not Defined";
  }
}

int Autonomous::addProgram(AutoProgram& p_program){
  switch ((int)p_program.getAutoSide()) {
    case AUTO_RED:
      m_redPrograms.push_back(&p_program);
      m_redProgramNames.at(p_program.getProgramNumber()) = p_program.getName();
      break;
    case AUTO_BLUE:
      m_bluePrograms.push_back(&p_program);
      m_blueProgramNames.at(p_program.getProgramNumber()) = p_program.getName();
      break;
    case AUTO_SKILLS:
      m_skillsPrograms.push_back(&p_program);
      m_skillsProgramNames.at(p_program.getProgramNumber()) = p_program.getName();
      break;
  }
  return 0;
}

AutoProgram* Autonomous::findProgram(const std::string p_name, const AutonomousSide p_autoSide){
  switch ((int)p_autoSide) {
    case AUTO_RED:
      for(int x = 0; x < m_redPrograms.size(); x++)
        if(m_redPrograms.at(x)->getName() == p_name)
          return m_redPrograms.at(x);
      break;
    case AUTO_BLUE:
      for(int x = 0; x < m_bluePrograms.size(); x++)
        if(m_bluePrograms.at(x)->getName() == p_name)
          return m_bluePrograms.at(x);
      break;
    case AUTO_SKILLS:
      for(int x = 0; x < m_skillsPrograms.size(); x++)
        if(m_skillsPrograms.at(x)->getName() == p_name)
          return m_skillsPrograms.at(x);
      break;
  }
  return NULL;
}

int Autonomous::defineGUI(const std::string p_returnScreenID){
  graphicalInterface& l_gui = m_robot.getGUI();

  l_gui.addScreen("Autonomous Selector");
  l_gui.addLabel("Autonomous Selector", 200, 10, redText, "Autonomous Selector");
  l_gui.addRectangle("Autonomous Selector", 0, 0, 480, 40, whiteText);

  l_gui.addButton("Autonomous Selector", "Button 1", 300, 60, 140, 30);
  l_gui.addButtonScreenChange("Autonomous Selector", "Button 1", "Home");
  l_gui.addButtonTextChange("Autonomous Selector", "Button 1", )
  return 0;
}

int Autonomous::task(){
  return 0;
}
