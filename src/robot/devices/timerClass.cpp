#include "robot/devices/timerClass.h"

Timer::Timer(const bool mode){
  if(mode){
    m_startTime = pros::millis();
    m_lastCheck = pros::millis();
    m_nextFlag = pros::millis();
  }
  else{
    m_startTime = 0;
    m_lastCheck = pros::millis();
    m_nextFlag = pros::millis();
  }
}

int Timer::resetTime(){
  m_startTime = pros::millis();
  return 1;
}

int Timer::getTime(){
  m_currentTime = pros::millis() - m_startTime;
  m_lastCheck = m_currentTime;
  return m_currentTime;
}

int Timer::timeElapsed(){
  m_currentTime = pros::millis() - m_startTime;
  int tempTime = m_currentTime - m_lastCheck;
  m_lastCheck = m_currentTime;
  return tempTime;
}

bool Timer::preformAction(const int delay){
  m_currentTime = pros::millis() - m_startTime;
  if(m_currentTime > m_nextFlag){
    m_nextFlag = m_currentTime+delay;
    return true;
  }
  else{
    return false;
  }
}
