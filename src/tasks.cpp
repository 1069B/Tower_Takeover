#include "tasks.hpp"
#include "robot/graphical/components/alertClass.hpp"

Robot robot;

void initialize(){
  pros::delay(5);
}

void disabled() {
  // robot.disabled();
}

void competition_initialize() {

}

void autonomous() {
  robot.disabled();
}

void opcontrol(){
  pros::delay(5);
  while(true){
    robot.task();
    pros::delay(5);
  }
}
