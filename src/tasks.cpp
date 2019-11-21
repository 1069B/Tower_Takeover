#include "tasks.hpp"

Robot robot;

void initialize(){
}

void disabled() {

}

void competition_initialize() {

}

void autonomous() {
  robot.autonmous();
}

void opcontrol(){
  while(true){
    robot.task();
    pros::delay(5);
  }
}
