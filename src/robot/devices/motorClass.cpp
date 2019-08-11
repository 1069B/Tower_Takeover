#include "robot/devices/motorClass.h"

Motor::Motor(std::string theName, short input, pros::motor_gearset_e_t type, bool reverse){
  name = theName;
  port = input;
  motorGearSet = type;
  reversed = reverse;
  internalPID = true;

  pros::c::motor_set_reversed(port, reversed);
  pros::c::motor_set_gearing(port, type);
  pros::c::motor_set_brake_mode(port, pros::E_MOTOR_BRAKE_COAST);
  pros::c::motor_set_encoder_units(port, pros::E_MOTOR_ENCODER_DEGREES);

  gui.addScreen(name);
  gui.addLabel(name, 200, 10, redText, name);
  gui.addRectangle(name, 0, 0, 480, 40, whiteText);

  gui.addLabel(name, 20, 50, whiteText, "Desired Velocity: %d", &desiredVelocity);
  gui.addLabel(name, 20, 80, whiteText, "Actual Velocity: %d", (std::function<int()>)std::bind(&Motor::getVelocity, this));
  gui.addLabel(name, 20, 110, whiteText, "Position: %d Deg", (std::function<int()>)std::bind(&Motor::getRotation, this));
  gui.addLabel(name, 20, 140, whiteText, "Reversed: %b", &reversed);
  gui.addLabel(name, 20, 170, whiteText, "Motor Gearset: %s", &s_gearSet);

  gui.addLabel(name, 260, 50, whiteText, "Desired Voltage: %d", &desiredVoltage);
  gui.addLabel(name, 260, 80, whiteText, "Actual Voltage: %d", (std::function<int()>)std::bind(&Motor::getVoltage, this));
  gui.addLabel(name, 260, 110, whiteText, "Tempature: %d C", (std::function<int()>)std::bind(&Motor::getTempature, this));
  gui.addLabel(name, 260, 140, whiteText, "Internal PID: %b", &internalPID);
  gui.addLabel(name, 260, 170, whiteText, "Brake Mode: %s", &s_brake);

  gui.addButton(name, 0, 160, 200, 150, 20);
  gui.addButtonAction(name, 0, "Go Back", "Home");

  gui.addRelationship(name, (std::function<bool()>)std::bind(&Motor::isConnected, this), "No_Device", true);
  setStrings();
}

void Motor::setVelocity(int vel){
  pros::c::motor_move_velocity(port, vel);
  desiredVelocity = vel;
  internalPID = true;
  desiredVoltage = 0;
}

void Motor::setVoltage(int pow){
  pros::c::motor_move_voltage(port, pow);
  desiredVoltage = pow;
  internalPID = false;
  desiredVelocity = 0;
}

void Motor::setBrake(pros::motor_brake_mode_e_t brake){
  pros::c::motor_set_brake_mode(port, brake);
  brakeMode = brake;
  setStrings();
}

void Motor::resetRotation(){
  pros::c::motor_tare_position(port);
}

bool Motor::isConnected(){
  return !(getTempature() == 2147483647);
}

int Motor::getVelocity(){
  return pros::c::motor_get_actual_velocity(port);
}

int Motor::getVoltage(){
  return pros::c::motor_get_voltage(port);
}

int Motor::getRotation(){
  return pros::c::motor_get_position(port);
}

int Motor::getTempature(){
  return pros::c::motor_get_temperature(port);
}

void Motor::setStrings(){
  if(motorGearSet == pros::E_MOTOR_GEARSET_36)
    s_gearSet = "100 RPM";
  else if(motorGearSet == pros::E_MOTOR_GEARSET_18)
    s_gearSet = "200 RPM";
  else
    s_gearSet = "600 RPM";

  if(brakeMode == pros::E_MOTOR_BRAKE_COAST)
    s_brake = "Coast";
  else if(brakeMode == pros::E_MOTOR_BRAKE_BRAKE)
    s_brake = "Brake";
  else
    s_brake = "Hold";
}
