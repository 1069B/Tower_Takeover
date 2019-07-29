#include "main.h"

#ifndef CONTROLAXISCLASS_H
#define CONTROLAXISCLASS_H

class ControlAxis{
private:
  pros::controller_id_e_t controllerType;
  pros::controller_analog_e_t axisType;
  double multiplier = 1;

public:
  ControlAxis(pros::controller_id_e_t controller, pros::controller_analog_e_t type);

  void setMultiplier(int mult);

  int getValue();

  int getPercent();
};
#endif // CONTROLAXISCLASS_H
