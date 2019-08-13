#include "main.h"

#ifndef TIMERCLASS_H
#define TIMERCLASS_H

  class Timer{
  private:
    int m_startTime;
    int m_currentTime;
    int m_lastCheck;
    int m_nextFlag;

  public:
    Timer(const bool mode = false);

    int resetTime();

    int getTime();

    int getLastCheck();

    int timeElapsed();

    bool preformAction();

    int addActionDelay(const int delay);
  };
#endif // TIMERCLASS_H
