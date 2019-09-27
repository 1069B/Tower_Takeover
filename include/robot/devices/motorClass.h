#include "main.h"
#include "robot/graphical/GUIClass.h"

#ifndef MOTORCLASS_H
#define MOTORCLASS_H

class Motor{
private:
  std::string m_name = "Motor";
  short m_port;
  pros::motor_gearset_e_t m_motorGearSet;
  std::string m_gearSetString = "200 RPM";
  pros::motor_brake_mode_e_t m_brakeMode;
  std::string m_brakeString = "Coast";
  int m_desiredVelocity;
  int m_desiredVoltage;
  bool m_reversed;
  bool m_internalPID;

  void setStrings();

public:
  Motor(std::string theName, short input, pros::motor_gearset_e_t type, bool reverse);

  void setVelocity(int vel);// In RPM

  void setVoltage(int pow);

  void setBrake(pros::motor_brake_mode_e_t brake);

  void resetRotation();

  bool isConnected();

  int getVelocity();

  int getVoltage();

  int getRotation();

  int getTempature();
};
#endif // MOTORCLASS_H
