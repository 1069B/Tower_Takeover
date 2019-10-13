#include "main.h"
#include "robot/devices/motorClass.hpp"
#include "robot/devices/controller/controllerClass.hpp"

#ifndef BASECLASS_H
#define BASECLASS_H

class Base{
protected:
  Motor* m_frontLeft;
  Motor* m_frontRight;
  Motor* m_backLeft;
  Motor* m_backRight;
  Motor* m_center;

  

  Controller m_driveController;

  int calculatePosition();

  Base();

  int drive();

};

#endif // BASECLASS_H
