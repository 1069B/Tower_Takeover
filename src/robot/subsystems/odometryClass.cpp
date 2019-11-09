#include "robot/subsystems/odometryClass.hpp"
#include "robotClass.hpp"

Odometry::Odometry(Robot& p_robot, std::string p_leftEncoder, std::string p_rightEncoder, std::string p_centerEncoder):
m_robot(p_robot){
  if(Encoder::findEncoder(p_leftEncoder) == NULL)
    m_leftEncoder = new Encoder(p_leftEncoder, 1, false);
  else
    m_leftEncoder = Encoder::findEncoder(p_leftEncoder);

  if(Encoder::findEncoder(p_rightEncoder) == NULL)
    m_rightEncoder = new Encoder(p_rightEncoder, 3, false);
  else
    m_rightEncoder = Encoder::findEncoder(p_rightEncoder);

  if(Encoder::findEncoder(p_centerEncoder) == NULL)
    m_centerEncoder = new Encoder(p_centerEncoder, 5, false);
  else
    m_centerEncoder = Encoder::findEncoder(p_centerEncoder);
}

int Odometry::getOrientation(){
  return 0;
}

int Odometry::getOrientationVelocity(){
  return 0;
}

int Odometry::setOrientation(int p_orientation){
  m_orientation = p_orientation;
  return 0;
}

int Odometry::getXposition(){
  return 0;
}

int Odometry::getXVelocity(){
  return 0;
}

int Odometry::setXposition(int p_xPosition){
  m_xPosition = p_xPosition;
  return 0;
}

int Odometry::getYposistion(){
  return 0;
}

int Odometry::getYVelocity(){
  return 0;
}

int Odometry::setYposition(int p_yPosition){
  m_yPosition = p_yPosition;
  return 0;
}

int Odometry::defineGUI(std::string p_returnScreen){
  graphicalInterface& l_gui = m_robot.m_gui;
  m_leftEncoder->defineGUI(l_gui, "Odometry");
  m_centerEncoder->defineGUI(l_gui, "Odometry");
  m_rightEncoder->defineGUI(l_gui, "Odometry");

  l_gui.addScreen(m_name);
  l_gui.addLabel(m_name, 200, 10, redText, m_name);
  l_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  l_gui.addLabel(m_name, 20, 50, whiteText, "Orientation: %d Deg", &m_orientation);
  l_gui.addLabel(m_name, 20, 75, whiteText, "Orientation Velocity: %d", (std::function<int()>)std::bind(&Odometry::getOrientationVelocity, this));
  l_gui.addLabel(m_name, 20, 100, whiteText, "Current XPosition: %d", &m_xPosition);
  l_gui.addLabel(m_name, 20, 125, whiteText, "Velocity of XPosition: %d", (std::function<int()>)std::bind(&Odometry::getXVelocity, this));
  l_gui.addLabel(m_name, 20, 150, whiteText, "Current YPosition: %d", &m_yPosition);
  l_gui.addLabel(m_name, 20, 175, whiteText, "Velocity of YPosition: %d", (std::function<int()>)std::bind(&Odometry::getYVelocity, this));

  l_gui.addButton(m_name, 0, 300, 60, 140, 30);
  l_gui.addButtonAction(m_name, 0, m_leftEncoder->getName(), m_leftEncoder->getName());
  l_gui.addButton(m_name, 1, 300, 100, 140, 30);
  l_gui.addButtonAction(m_name, 1, m_centerEncoder->getName(), m_centerEncoder->getName());
  l_gui.addButton(m_name, 2, 300, 140, 140, 30);
  l_gui.addButtonAction(m_name, 2, m_rightEncoder->getName(), m_rightEncoder->getName());

  l_gui.addButton(m_name, 3, 160, 200, 150, 25);
  l_gui.addButtonAction(m_name, 3, "Go Back", p_returnScreen);
  return 0;
}
