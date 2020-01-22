#include "timerClass.hpp"

#ifndef TASKSCHEDCLASS_H
#define TASKSCHEDCLASS_H

class Robot;

enum CallType{
    DURING_AUTO = 0,
    DURING_OPERATER = 1,
    ALWAYS = 2
};

enum CompMode{
    AUTO = 0,
    OPERATER = 1,
    DISABLED = 2
};

struct SubTask{
private:
    std::string m_name;
    std::function<int()> m_function;
    int m_callPeriod = 50;
    int m_callFrequency = 0;
    Timer m_timer;
    CallType m_callType;
    friend class TaskScheduler;
public:
    SubTask(std::string p_name, std::function<int()> p_function, int p_callPeriod, CallType p_callType);

    std::string getName();

    std::function<int()> getFunction();

    int getCallPeriod();

    int getCallFrequency();

    CallType getCallType();
};

class TaskScheduler{
private:
    Robot &m_robot;
    std::string m_name;
    std::vector<SubTask*> m_taskArray;
    CompMode m_compMode;
public:
    TaskScheduler(Robot &l_robot, std::string p_name);

    int addTask(std::string p_name, std::function<int()> p_callBack, int p_callPeriod, CallType p_callType);

    int task();

    int setCompMode(CompMode p_compMode);

    int defineGUI();

    SubTask* findTask(std::string p_name);
};

#endif // TASKSCHEDCLASS_H
