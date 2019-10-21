#include "robot/devices/encoderClass.hpp"

ExternalFile Encoder::s_config("Motor_Config.txt");
std::vector<Encoder*> Encoder::s_encoderArray;

Encoder::Encoder(const std::string p_name ,const int p_port){
  m_name = p_name;
  m_port = p_port;
  pros::c::adi_encoder_init(m_port, m_port+1, false);
  s_encoderArray.push_back(this);
}

bool Encoder::isConnected(){
  if(getRotation() == 2147483647)// Needs to change detection methoud
    return true;
  return false;
}

int Encoder::getRotation(){
  m_rotation = pros::c::adi_encoder_get(m_port);
  return m_rotation;
}

int Encoder::resetRotation(){
  m_zeroPosition = pros::c::adi_encoder_get(m_port);
  return 0;
}

int Encoder::getVelocity(){
  double l_distanceChange = getRotation() - m_previousRotation;
  double l_timeChange = (m_timer.getTime() - m_previousTime) / 1000.0;

  m_velocity = l_distanceChange / l_timeChange;

  m_previousTime = m_timer.getTime();
  m_previousRotation = getRotation();
  return m_velocity;
}

int Encoder::changePort(const short p_port){
  m_port = p_port;
  pros::c::adi_encoder_init(m_port, m_port+1, false);
  return 0;
}

int Encoder::defineGUI(graphicalInterface& p_gui, const std::string p_returnScreen){
  p_gui.addScreen(m_name);
  p_gui.addLabel(m_name, 200, 10, redText, m_name);
  p_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  p_gui.addLabel(m_name, 20, 50, whiteText, "Zero Position: %d", &m_zeroPosition);
  p_gui.addLabel(m_name, 20, 80, whiteText, "Previous Time: %d", &m_previousTime);
  p_gui.addLabel(m_name, 20, 110, whiteText, "Previous Rotation: %d Deg", &m_previousRotation);
  p_gui.addLabel(m_name, 20, 140, whiteText, "Rotation: %d Deg", (std::function<int()>)std::bind(&Encoder::getRotation, this));
  p_gui.addLabel(m_name, 20, 170, whiteText, "Velocity: %d", (std::function<int()>)std::bind(&Encoder::getVelocity, this));

  p_gui.addButton(m_name, 0, 160, 200, 150, 20);
  p_gui.addButtonAction(m_name, 0, "Go Back", p_returnScreen);

  p_gui.addRelationship(m_name, (std::function<bool()>)std::bind(&Encoder::isConnected, this), "No_Device", false);
  return 0;
}

Encoder* Encoder::findEncoder(const std::string p_name){
  for(int x = 0; x < s_encoderArray.size(); x++)
    if(s_encoderArray.at(x)->m_name == p_name)
      return s_encoderArray.at(x);
  return NULL;
}

Encoder* Encoder::findEncoder(const short p_port){
  for(int x = 0; x < s_encoderArray.size(); x++)
    if(s_encoderArray.at(x)->m_port == p_port)
      return s_encoderArray.at(x);
  return NULL;
}
