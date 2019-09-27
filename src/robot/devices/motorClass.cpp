#include "robot/devices/motorClass.h"

Motor::Motor(std::string p_name, short p_input, pros::motor_gearset_e_t p_type, bool p_reverse){
  m_name = p_name;
  m_port = p_input;
  m_motorGearSet = p_type;
  m_reversed = p_reverse;
  m_internalPID = true;

  pros::c::motor_set_reversed(m_port, m_reversed);
  pros::c::motor_set_gearing(m_port, p_type);
  pros::c::motor_set_brake_mode(m_port, pros::E_MOTOR_BRAKE_COAST);
  pros::c::motor_set_encoder_units(m_port, pros::E_MOTOR_ENCODER_DEGREES);

  gui.addScreen(m_name);
  gui.addLabel(m_name, 200, 10, redText, m_name);
  gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  gui.addLabel(m_name, 20, 50, whiteText, "Desired Velocity: %d", &m_desiredVelocity);
  gui.addLabel(m_name, 20, 80, whiteText, "Actual Velocity: %d", (std::function<int()>)std::bind(&Motor::getVelocity, this));
  gui.addLabel(m_name, 20, 110, whiteText, "Position: %d Deg", (std::function<int()>)std::bind(&Motor::getRotation, this));
  gui.addLabel(m_name, 20, 140, whiteText, "Reversed: %b", &m_reversed);
  gui.addLabel(m_name, 20, 170, whiteText, "Motor Gearset: %s", &m_gearSetString);

  gui.addLabel(m_name, 260, 50, whiteText, "Desired Voltage: %d", &m_desiredVoltage);
  gui.addLabel(m_name, 260, 80, whiteText, "Actual Voltage: %d", (std::function<int()>)std::bind(&Motor::getVoltage, this));
  gui.addLabel(m_name, 260, 110, whiteText, "Tempature: %d C", (std::function<int()>)std::bind(&Motor::getTempature, this));
  gui.addLabel(m_name, 260, 140, whiteText, "Internal PID: %b", &m_internalPID);
  gui.addLabel(m_name, 260, 170, whiteText, "Brake Mode: %s", &m_brakeString);

  gui.addButton(m_name, 0, 160, 200, 150, 20);
  gui.addButtonAction(m_name, 0, "Go Back", "Home");

  gui.addRelationship(m_name, (std::function<bool()>)std::bind(&Motor::isConnected, this), "No_Device", true);
  setStrings();
}

void Motor::setVelocity(int p_velocity){
  pros::c::motor_move_velocity(m_port, p_velocity);
  m_desiredVelocity = p_velocity;
  m_internalPID = true;
  m_desiredVoltage = 0;
}

void Motor::setVoltage(int p_power){
  pros::c::motor_move_voltage(m_port, p_power);
  m_desiredVoltage = p_power;
  m_internalPID = false;
  m_desiredVelocity = 0;
}

void Motor::setBrake(pros::motor_brake_mode_e_t p_power){
  pros::c::motor_set_brake_mode(m_port, p_power);
  m_brakeMode = p_power;
  setStrings();
}

void Motor::resetRotation(){
  pros::c::motor_tare_position(m_port);
}

bool Motor::isConnected(){
  return !(getTempature() == 2147483647);
}

int Motor::getVelocity(){
  return pros::c::motor_get_actual_velocity(m_port);
}

int Motor::getVoltage(){
  return pros::c::motor_get_voltage(m_port);
}

int Motor::getRotation(){
  return pros::c::motor_get_position(m_port);
}

int Motor::getTempature(){
  return pros::c::motor_get_temperature(m_port);
}

void Motor::setStrings(){
  if(m_motorGearSet == pros::E_MOTOR_GEARSET_36)
    m_gearSetString = "100 RPM";
  else if(m_motorGearSet == pros::E_MOTOR_GEARSET_18)
    m_gearSetString = "200 RPM";
  else
    m_gearSetString = "600 RPM";

  if(m_brakeMode == pros::E_MOTOR_BRAKE_COAST)
    m_brakeString = "Coast";
  else if(m_brakeMode == pros::E_MOTOR_BRAKE_BRAKE)
    m_brakeString = "Brake";
  else
    m_brakeString = "Hold";
}
