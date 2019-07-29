#include "main.h"
#include "robot/graphical/GUIClass.h"

#ifndef MOTORCLASS_H
#define MOTORCLASS_H

class Motor{
private:
  std::string name = "Motor";
  short port;
  pros::motor_gearset_e_t motorGearSet;
  std::string s_gearSet = "200 RPM";
  pros::motor_brake_mode_e_t brakeMode;
  std::string s_brake = "Coast";
  int desiredVelocity;
  int desiredVoltage;
  bool reversed;
  bool internalPID;

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
