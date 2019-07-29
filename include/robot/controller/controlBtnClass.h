#include "main.h"

#ifndef CONTROLBTNCLASS_H
#define CONTROLBTNCLASS_H

class ControlBtn{
private:
  pros::controller_id_e_t controllerType;
  pros::controller_digital_e_t buttonType;
  bool callBackState = false;
  std::function<void()> callBack;
  int callBackDelay = 0;
  int lastCall = 0;

public:
  ControlBtn(pros::controller_id_e_t controller, pros::controller_digital_e_t type);

  void setCallBack(std::function<void()> func, int delay);

  void checkCallBack();

  bool state();
};
#endif // CONTROLBTNCLASS_H
