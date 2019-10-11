#include "tasks.hpp"

Motor motor_1("Motor_1", 1, pros::E_MOTOR_GEARSET_18, false);

Robot robot;

void initialize(){
  robot = Robot();
}

void disabled() {

}

void competition_initialize() {

}

void autonomous() {

}

void opcontrol(){
  while(true){
    robot.task();
    pros::delay(100);
  }
}
