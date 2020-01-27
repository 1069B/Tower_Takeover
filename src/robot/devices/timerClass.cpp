#include "robot/devices/timerClass.hpp"

Timer::Timer(const bool p_mode){// False is system time
  if(p_mode){
    m_startTime = pros::millis();
    m_nextFlag.push_back(pros::millis());
    m_previousLapTime.push_back(pros::millis());
  }
  else{
    m_startTime = 0;
    m_nextFlag.push_back(0);
    m_previousLapTime.push_back(0);
  }
}

int Timer::resetTime(){
  m_startTime = pros::millis();
  for(int x = 0; x < m_previousLapTime.size(); x++)
    m_previousLapTime.at(x) = pros::millis();
  for(int x = 0; x < m_nextFlag.size(); x++)
    m_nextFlag.at(x) = pros::millis();
  return 1;
}

int Timer::getTime(){
  m_currentTime = pros::millis() - m_startTime;
  return m_currentTime;
}

int Timer::lapTime(const int p_lapVersion){
  m_currentTime = pros::millis() - m_startTime;
  if(m_previousLapTime.size() <= p_lapVersion){
    for(int x = 0; x< ((m_previousLapTime.size()+1)-p_lapVersion); x++){
      m_previousLapTime.push_back(0);
    }
  }
  int lapDuration = m_currentTime - m_previousLapTime.at(p_lapVersion);
  m_previousLapTime.at(p_lapVersion) = m_currentTime;
  return lapDuration;
}

bool Timer::preformAction(const int p_actionVersion){
  m_currentTime = pros::millis() - m_startTime;
  if(m_nextFlag.size() <= p_actionVersion){
    for(int x = 0; x< ((m_nextFlag.size()+1)-p_actionVersion); x++){
      m_nextFlag.push_back(INT_MAX);
    }
  }

  if(m_currentTime+1 >= m_nextFlag.at(p_actionVersion))//Plus 2 for 2 millisec threshold
    return true;
  else
    return false;
}

int Timer::addActionDelay(const int p_delay, const int p_actionVersion){
  m_currentTime = pros::millis() - m_startTime;

  if(m_nextFlag.size() <= p_actionVersion){
    for(int x = 0; x< ((m_nextFlag.size()+1)-p_actionVersion); x++){
      m_nextFlag.push_back(INT_MAX);
    }
  }

  m_nextFlag.at(p_actionVersion) = m_currentTime + p_delay;
  return 1;
}

int Timer::defineGUI(graphicalInterface& p_gui, std::string p_returnScreen){

  return 0;
}
