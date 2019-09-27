#include "main.h"

#ifndef CONTROLBTNCLASS_H
#define CONTROLBTNCLASS_H

class ControlBtn{
private:
  pros::controller_id_e_t m_controllerType;
  pros::controller_digital_e_t m_buttonType;
  bool m_callBackState = false;
  std::function<void()> m_callBack;
  int m_callBackDelay = 0;
  int m_lastCall = 0;

public:
  ControlBtn(pros::controller_id_e_t p_controller, pros::controller_digital_e_t p_type);

  void setCallBack(std::function<void()> p_function, int p_delay);

  void checkCallBack();

  bool state();
};
#endif // CONTROLBTNCLASS_H
