#include "tasks.hpp"
#include "robot/graphical/alertClass.hpp"

Robot robot;

void initialize(){

}

void disabled() {
  //robot.disabled();
}

void competition_initialize() {

}

void autonomous() {
  robot.disabled();
}

void opcontrol(){
  defineStyles();
  while(true){
    robot.task();
    pros::delay(5);
  }
}
