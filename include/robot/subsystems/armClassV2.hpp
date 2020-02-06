#include "robot/devices/motorClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"
#include "robot/graphical/GUIClass.hpp"

class Robot;

#ifndef ARMCLASS_H
#define ARMCLASS_H

class ArmV2 {
private:
  Robot& m_robot;
  Motor* m_armMotor;

public:
  ArmV2(Robot& p_robot);

  int task();
};

#endif // LIFTCLASS_H
