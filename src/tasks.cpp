#include "tasks.hpp"

Robot robot;

void initialize(){
}

void disabled() {
  robot.disabled();
}

void competition_initialize() {

}

void autonomous() {
  robot.disabled();
}

void opcontrol(){
  while(true){
    robot.task();
    pros::delay(5);
  }
}
