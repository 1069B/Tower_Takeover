#include "robotClass.hpp"

int x =0;
int a =0;

int Robot::defineGUI(){
  defineStyles();
  m_mainController.defineGUI(m_gui, "Home");
  m_partnerController.defineGUI(m_gui, "Home");

  m_gui.addScreen("Home");
  //m_gui.addLabel("Home", 20, 20, whiteText, "Motor_1 Connected: %b", (std::function<bool()>) std::bind(&Motor::isConnected, &motor_1));
  m_gui.addButton("Home", 0, 300, 100, 150, 30);
  m_gui.addButtonAction("Home", 0, "Timer 1", "Timer1");
  m_gui.addButton("Home", 4, 150, 100, 150, 30);
  m_gui.addButtonAction("Home", 4, "Encoder 1", "Enc1");
  m_gui.addButton("Home", 1, 150, 150, 150, 30);
  m_gui.addButtonAction("Home", 1,"Main Controller", "Main Controller");
  m_gui.addButton("Home", 2, 50, 20, 150, 30, x);
  m_gui.addButtonCounter("Home", 2, "+1", 0, 1);
  m_gui.addButton("Home", 3, 300, 20, 150, 30, x);
  m_gui.addButtonCounter("Home", 3, "-1", 0, -1);
  m_gui.addLabel("Home", 20, 200, whiteText, "SD Card is Connected: %b", (std::function<bool()>) &ExternalFile::SDCardIsInserted);
  m_gui.addLabel("Home", 200, 20, whiteText, "X: %d", &x);

  m_gui.addScreen("Settings");
  m_gui.addLabel("Settings", 20, 20, whiteText, "Comp");

  m_gui.addScreen("No_Device");
  m_gui.addLabel("No_Device", 150, 100, whiteText, "Device Not Connected");
  //m_gui.addButton("No_Device", 0, 160, 200, 150, 20);
  //m_gui.addButtonAction("No_Device", 0,"Go Back", "Home");

  m_gui.addScreen("Timer1");
  m_gui.addLabel("Timer1", 20, 20, whiteText, "Timer1: %d millis", (std::function<int()>) std::bind(&Timer::getTime, &m_timer));
  m_gui.addLabel("Timer1", 20, 50, whiteText, "Timer1: %d lapTime", (std::function<int()>) std::bind(&Timer::lapTime, &m_timer));

  //m_gui.addLabel("Timer1", 20, 110, whiteText, "Calcs per sec %d", &a);


  //m_gui.addButton("Timer1", 0, 160, 200, 150, 20);
  //m_gui.addButtonAction("Timer1", 0,"Go Back", "Home");
  return 0;
}
