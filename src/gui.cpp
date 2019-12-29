#include "robotClass.hpp"

int x =0;
int a =0;
bool c = true;

int Robot::defineGUI(){
  defineStyles();
  m_mainController.defineGUI(m_gui, "Home");
  m_partnerController.defineGUI(m_gui, "Home");
  m_base.defineGUI("Home");

  m_gui.addScreen("Home");
  m_gui.addButton("Home", "Odometry", 150, 100, 150, 30);
  m_gui.addButtonScreenChange("Home", "Odometry", "Odometry");
  m_gui.addButton("Home", "Main Controller", 150, 150, 150, 30);
  m_gui.addButtonScreenChange("Home", "Main Controller", "Main Controller");
  m_gui.addButton("Home", "+1", 20, 20, 150, 30);
  m_gui.addButtonVaribleCounter("Home", "+1", &x, 1);
  m_gui.addButton("Home", "-1", 300, 20, 150, 30);
  m_gui.addButtonVaribleCounter("Home", "-1", &x, -1);
  m_gui.addLabel("Home", 20, 200, whiteText, "SD Card is Connected: %b", (std::function<bool()>) &ExternalFile::SDCardIsInserted);
  m_gui.addLabel("Home", 200, 20, whiteText, "X: %d", &x);
  m_gui.addToggle("Home", 20, 80, 75, 30, &c);

  // m_gui.addScreen("Settings");
  // m_gui.addLabel("Settings", 20, 20, whiteText, "Comp");

  m_gui.addScreen("No_Device");
  m_gui.addLabel("No_Device", 150, 100, whiteText, "Device Not Connected");
  m_gui.addButton("No_Device", "Go Back", 160, 200, 150, 20);
  m_gui.addButtonScreenChange("No_Device", "Go Back", "Home");

  m_gui.addScreen("No_Screen_Found");
  m_gui.addLabel("No_Screen_Found", 150, 100, whiteText, "Screen Not Found");
  m_gui.addButton("No_Screen_Found", "Go Back", 160, 200, 150, 20);
  m_gui.addButtonScreenChange("No_Screen_Found", "Go Back", "Home");

  // m_gui.addScreen("Timer1");
  // m_gui.addLabel("Timer1", 20, 20, whiteText, "Timer1: %d millis", (std::function<int()>) std::bind(&Timer::getTime, &m_timer));
  // m_gui.addLabel("Timer1", 20, 50, whiteText, "Timer1: %d lapTime", (std::function<int()>) std::bind(&Timer::lapTime, &m_timer));

  //m_gui.addLabel("Timer1", 20, 110, whiteText, "Calcs per sec %d", &a);


  //m_gui.addButton("Timer1", 0, 160, 200, 150, 20);
  //m_gui.addButtonAction("Timer1", 0,"Go Back", "Home");
  return 0;
}
