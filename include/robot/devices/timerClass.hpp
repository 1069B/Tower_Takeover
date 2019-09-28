#include "main.h"

#ifndef TIMERCLASS_H
#define TIMERCLASS_H

  class Timer{
  private:
    int m_startTime;
    int m_currentTime;
    int m_previousLapTime;
    int m_nextFlag;

  public:
    Timer(const bool p_mode = false);

    int resetTime();

    int getTime();

    int lapTime();

    bool preformAction();

    int addActionDelay(const int p_delay);
  };
#endif // TIMERCLASS_H
