#include "robot/varibleDecleration.hpp"
#include "robot/devices/timerClass.hpp"

class Robot;

#ifndef ARMCLASSV2_H
#define ARMCLASSV2_H

class ArmV2 {
private:
  Robot& m_robot;
  Motor* m_armMotor;

public:
  ArmV2(Robot& p_robot);

  int task();
};

#endif // ARMCLASSV2_H
