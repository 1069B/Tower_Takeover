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
  int x =0;
  // while(x < 200){
  //   //robot.task();
  //   pros::delay(5);
  //   x++;
  // }
  pros::delay(5);

}
