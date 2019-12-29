#include "tasks.hpp"
#include "robot/graphical/components/alertClass.hpp"

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
  pros::delay(5);
/*Copy the first switch and turn it ON*/

  // while(true){
  //   robot.task();
  //   pros::delay(5);
  // }
}
