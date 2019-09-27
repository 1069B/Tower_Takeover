#include "main.h"

#ifndef CONTROLAXISCLASS_H
#define CONTROLAXISCLASS_H

class ControlAxis{
private:
  pros::controller_id_e_t m_controllerType;
  pros::controller_analog_e_t m_axisType;
  double m_multiplier = 1;

public:
  ControlAxis(pros::controller_id_e_t p_controller, pros::controller_analog_e_t p_type);

  void setMultiplier(int p_mult);

  int getValue();

  int getPercent();
};
#endif // CONTROLAXISCLASS_H
