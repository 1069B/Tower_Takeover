#include "tasks.h"
graphicalInterface gui("Timer1");
Controller mainController(pros::E_CONTROLLER_MASTER);
Controller partnerController(pros::E_CONTROLLER_PARTNER);

Motor motor_1("Motor_1", 1, pros::E_MOTOR_GEARSET_18, false);
int x =0;
int a =0;

Timer timer1(false);
int time = 0;
int getElapsed = 0;
int lastCheck = 0;

void initialize() {
  defineStyles();
  /*Create a simple base object*/

  gui.addScreen("Home");
  //gui.addLabel("Home", 20, 20, whiteText, "Motor_1 Connected: %b", (std::function<bool()>) std::bind(&Motor::isConnected, &motor_1));
  gui.addButton("Home", 0, 300, 100, 150, 30);
  gui.addButtonAction("Home", 0, "Timer 1", "Timer1");

  gui.addButton("Home", 4, 150, 100, 150, 30);
  gui.addButtonAction("Home", 4, "Motor 1", "Motor_1");

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



  gui.addScreen("Timer1");
  gui.addLabel("Timer1", 20, 20, whiteText, "Timer1: %d millis", (std::function<int()>) std::bind(&Timer::getTime, &timer1));
  gui.addLabel("Timer1", 20, 50, whiteText, "Timer1: %d lapTime", (std::function<int()>) std::bind(&Timer::lapTime, &timer1));

  gui.addLabel("Timer1", 20, 110, whiteText, "Calcs per sec %d", &a);

  gui.addButton("Timer1", 0, 160, 200, 150, 20);
  gui.addButtonAction("Timer1", 0,"Go Back", "Home");
}

void disabled() {

}

void competition_initialize() {

}

void autonomous() {

}

void opcontrol(){
  while(pros::millis() < 1000){
    gui.task();// Function For Meaurement
    a++;
  }

  ExternalFile file1 = ExternalFile("Robot_Info.txt");

  std::vector<std::string> vec;
  vec.push_back("true");
  vec.push_back("false");
  vec.push_back("Schanker");
  vec.push_back("Mizer");

  file1.storeStringArray("Var1", vec);


    std::vector<float> vec2;
    vec2.push_back(3.1415);
    vec2.push_back(345.098);
    vec2.push_back(0.002);
    vec2.push_back(0.240);

    file1.storeDoubleArray("Var1", vec2);

  while(true){
    gui.task();
    mainController.callBackCheck();

    if(timer1.preformAction()){
      time = timer1.getTime();
      lastCheck = timer1.lapTime();
      timer1.addActionDelay(500);
    }

    pros::delay(100);
  }
}
