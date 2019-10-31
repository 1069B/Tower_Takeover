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

int Odometry::defineGUI(std::string p_returnScreen){
  graphicalInterface& l_gui = m_robot.m_gui;
  l_gui.addScreen(m_name);
  l_gui.addLabel(m_name, 200, 10, redText, m_name);
  l_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  l_gui.addLabel(m_name, 20, 50, whiteText, "Orientation: %d Deg", &m_orientation);
  l_gui.addLabel(m_name, 20, 80, whiteText, "Current XPosition: %d", &m_currentX);
  l_gui.addLabel(m_name, 20, 80, whiteText, "Current YPosition: %d", &m_currentY);
  l_gui.addLabel(m_name, 20, 80, whiteText, "Target XPosition: %d", &m_targetX);
  l_gui.addLabel(m_name, 20, 80, whiteText, "Target YPosition: %d", &m_targetY);
  l_gui.addLabel(m_name, 20, 140, whiteText, "Current Action: %d ", &m_actionName);

  l_gui.addButton(m_name, 0, 20, 150, 150, 20);
  l_gui.addButtonAction(m_name, 0, m_leftEncoder->getName(), m_leftEncoder->getName());
  l_gui.addButton(m_name, 0, 200, 150, 150, 20);
  l_gui.addButtonAction(m_name, 0, m_centerEncoder->getName(), m_centerEncoder->getName());
  l_gui.addButton(m_name, 0, 380, 150, 150, 20);
  l_gui.addButtonAction(m_name, 0, m_centerEncoder->getName(), m_centerEncoder->getName());

  l_gui.addButton(m_name, 0, 160, 200, 150, 20);
  l_gui.addButtonAction(m_name, 0, "Go Back", p_returnScreen);
  return 0;
}
