#include "tasks.hpp"
#include "robot/graphical/components/alertClass.hpp"

Robot robot;

void initialize(){
  g_alert.draw("Got to opcontrol");
}

void disabled() {
  //robot.disabled();
}

void competition_initialize() {

}

void autonomous() {
  //robot.disabled();
}

void opcontrol(){

  while(true){
    robot.task();
    pros::delay(5);
  }
}
