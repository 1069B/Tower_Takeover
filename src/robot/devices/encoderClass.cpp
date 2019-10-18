#include "robot/devices/encoderClass.hpp"

Encoder::Encoder(const std::string p_name ,const int p_port){
  m_name = p_name;
  m_port = p_port;
}

bool Encoder::isConnected(){
  if(getRotation() == 2147483647)
    return true;
  return false;
}

int Encoder::getRotation(){
  m_rotation = pros::c::adi_encoder_get(pros::c::adi_encoder_t(m_port)) - m_zeroPosition;// Add gettter methoud
  return m_rotation;
}

int Encoder::resetRotation(){
  m_zeroPosition = pros::c::adi_encoder_get(pros::c::adi_encoder_t(m_port));
  return 0;
}

int Encoder::getVelocity(){
  int l_distanceChange = getRotation() - m_previousPosition;
  int l_timeChange = m_timer.getTime() - m_previousTime;

  m_velocity = l_distanceChange / l_timeChange;

  m_previousTime = m_timer.getTime();
  m_previousPosition = getRotation();
  return m_velocity;
}

int Encoder::defineGUI(){
  return 0;
}

int Encoder::changePort(const short p_port){
  m_port = p_port;
  return 0;
}
