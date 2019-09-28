#include "robot/devices/timerClass.h"

Timer::Timer(const bool p_mode){// False is system time
  if(p_mode){
    m_startTime = pros::millis();
    m_nextFlag = pros::millis();
    m_previousLapTime = pros::millis();
  }
  else{
    m_startTime = 0;
    m_nextFlag = 0;
    m_previousLapTime = 0;
  }
}

int Timer::resetTime(){
  m_startTime = pros::millis();
  m_previousLapTime = pros::millis();
  return 1;
}

int Timer::getTime(){
  m_currentTime = pros::millis() - m_startTime;
  return m_currentTime;
}

int Timer::lapTime(){
  m_currentTime = pros::millis() - m_startTime;
  int lapDuration = m_currentTime - m_previousLapTime;
  m_previousLapTime = m_currentTime;
  return lapDuration;
}

bool Timer::preformAction(){
  m_currentTime = pros::millis() - m_startTime;
  if(m_currentTime+2 >= m_nextFlag)//Plus 2 for 2 millisec threshold
    return true;
  else
    return false;
}

int Timer::addActionDelay(const int p_delay){
  m_currentTime = pros::millis() - m_startTime;
  m_nextFlag = m_currentTime + p_delay;
  return 1;
}
