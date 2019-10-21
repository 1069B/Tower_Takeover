#include "robot/devices/encoderClass.hpp"

RedEncoder::RedEncoder(const std::string p_name ,const int p_port){
  m_name = p_name;
  m_port = p_port;
  pros::c::adi_encoder_init(m_port, m_port+1, false);
}

bool RedEncoder::isConnected(){
  if(getRotation() == 2147483647)
    return true;
  return false;
}

int RedEncoder::getRotation(){
  m_rotation = pros::c::adi_encoder_get(m_port);
  return m_rotation;
}

int RedEncoder::resetRotation(){
  m_zeroPosition = pros::c::adi_encoder_get(m_port);
  return 0;
}

int RedEncoder::getVelocity(){
  double l_distanceChange = getRotation() - m_previousRotation;
  double l_timeChange = (m_timer.getTime() - m_previousTime) / 1000.0;

  m_velocity = l_distanceChange / l_timeChange;

  m_previousTime = m_timer.getTime();
  m_previousRotation = getRotation();
  return m_velocity;
}

int RedEncoder::defineGUI(){
  return 0;
}

int RedEncoder::changePort(const short p_port){
  m_port = p_port;
  return 0;
}

int RedEncoder::defineGUI(graphicalInterface& p_gui, std::string p_returnScreen){
  p_gui.addScreen(m_name);
  p_gui.addLabel(m_name, 200, 10, redText, m_name);
  p_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  p_gui.addLabel(m_name, 20, 50, whiteText, "Zero Position: %d", &m_zeroPosition);
  p_gui.addLabel(m_name, 20, 80, whiteText, "Previous Time: %d", &m_previousTime);
  p_gui.addLabel(m_name, 20, 110, whiteText, "Previous Rotation: %d Deg", &m_previousRotation);
  p_gui.addLabel(m_name, 20, 140, whiteText, "Rotation: %d Deg", (std::function<int()>)std::bind(&RedEncoder::getRotation, this));
  p_gui.addLabel(m_name, 20, 170, whiteText, "Velocity: %d", (std::function<int()>)std::bind(&RedEncoder::getVelocity, this));

  p_gui.addButton(m_name, 0, 160, 200, 150, 20);
  p_gui.addButtonAction(m_name, 0, "Go Back", p_returnScreen);

  p_gui.addRelationship(m_name, (std::function<bool()>)std::bind(&RedEncoder::isConnected, this), "No_Device", false);
  return 0;
}
