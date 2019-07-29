#include "tasks.h"
graphicalInterface gui = graphicalInterface("Home");
Controller mainController = Controller(pros::E_CONTROLLER_MASTER);
Controller partnerController = Controller(pros::E_CONTROLLER_PARTNER);

Motor motor_1 = Motor("Motor_1", 1, pros::E_MOTOR_GEARSET_18, false);
int x =0;
void initialize() {
  defineStyles();
  /*Create a simple base object*/

  gui.addScreen("Home");
  //gui.addLabel("Home", 20, 20, whiteText, "Motor_1 Connected: %b", (std::function<bool()>) std::bind(&Motor::isConnected, &motor_1));
  gui.addButton("Home", 0, 150, 100, 150, 30);
  gui.addButtonAction("Home", 0, "Motor 1", "Motor_1");
  gui.addButton("Home", 1, 150, 150, 150, 30);
  gui.addButtonAction("Home", 1,"Main Controller", "Main Controller");
  gui.addButton("Home", 2, 50, 20, 150, 30, x);
  gui.addButtonCounter("Home", 2, "+1", 0, 1);
  gui.addButton("Home", 3, 300, 20, 150, 30, x);
  gui.addButtonCounter("Home", 3, "-1", 0, -1);
  gui.addLabel("Home", 200, 20, whiteText, "X: %d", &x);

  gui.addScreen("No_Device");
  gui.addLabel("No_Device", 150, 100, whiteText, "Device Not Connected");
  gui.addButton("No_Device", 0, 160, 200, 150, 20);
  gui.addButtonAction("No_Device", 0,"Go Back", "Home");

  mainController.Axis1.setMultiplier(2);
  mainController.ButtonA.setCallBack((std::function<void()>) std::bind(&Motor::resetRotation, &motor_1), 5000);
}

void disabled() {

}

void competition_initialize() {

}

void autonomous() {

}

void opcontrol(){
  while(true){
    gui.task();
    mainController.callBackCheck();

    //motor_1.setVoltage(mainController.Axis1.getPercent());
    motor_1.setVelocity(mainController.Axis1.getPercent());
    pros::delay(100);
  }
}
