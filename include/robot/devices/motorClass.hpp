#include "main.h"
#include "robot/graphical/GUIClass.hpp"
#include "robot/devices/externalFileClass.hpp"

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

  static ExternalFile s_config;
  static std::vector<Motor*> s_motorArray;

public:
  Motor(const std::string p_name, const short p_input, const pros::motor_gearset_e_t p_type, const bool p_reverse);

  void setVelocity(const int p_velocity);// In RPM

  void setVoltage(const int p_power);

  void setBrake(const pros::motor_brake_mode_e_t p_power);

  void resetRotation();

  bool isConnected();

  int getVelocity();

  int getVoltage();

  int getRotation();

  int getTempature();

  int defineGUI(graphicalInterface& p_gui, std::string p_returnScreen);

  static Motor* findMotor(std::string p_name);
};
#endif // MOTORCLASS_H
