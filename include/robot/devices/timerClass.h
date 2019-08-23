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
    Timer(const bool mode = false);

    int resetTime();

    int getTime();

    int lapTime();

    bool preformAction();

    int addActionDelay(const int delay);
  };
#endif // TIMERCLASS_H
