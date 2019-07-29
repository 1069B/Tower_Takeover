#include "controlBtnClass.h"
#include "controlAxisClass.h"
#include "robot/graphical/GUIClass.h"

#ifndef CONTROLLERCLASS_H
#define CONTROLLERCLASS_H

class Controller{
private:
  pros::controller_id_e_t controllerType;
public:
  std::string name = "Controller";
  ControlBtn ButtonL1;
  ControlBtn ButtonL2;
  ControlBtn ButtonR1;
  ControlBtn ButtonR2;
  ControlBtn ButtonUp;
  ControlBtn ButtonDown;
  ControlBtn ButtonLeft;
  ControlBtn ButtonRight;
  ControlBtn ButtonX;
  ControlBtn ButtonB;
  ControlBtn ButtonY;
  ControlBtn ButtonA;
  ControlAxis Axis1;
  ControlAxis Axis2;
  ControlAxis Axis3;
  ControlAxis Axis4;

  Controller(pros::controller_id_e_t type);

  void clear();

  void clearLine(int line);

  int getBatteryCapacity();

  int getBatteryLevel();

  bool isConnected();

  void print(int row, int col, const char* fmt...);

  void rumble(const char* fmt);

  void setText(int row, int col, const char* fmt);

  void callBackCheck();
};
#endif // CONTROLLERCLASS_H
