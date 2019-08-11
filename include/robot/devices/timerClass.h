#ifndef TIMERCLASS_H
#define TIMERCLASS_H

  class Timer{
  private:
    int m_startTime;
    int m_lastCheck;
    int m_delay;
    bool m_mode;

  public:
    Timer(bool mode = false);

    int resetTime();

    int getTime();

    int timeElasped();//Check spelling

    bool preformAction(int delay);
  };
#endif // TIMERCLASS_H
