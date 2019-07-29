#include "robot/controller/controllerClass.h"

Controller::Controller(pros::controller_id_e_t type):
  ButtonL1(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_L1)),
  ButtonL2(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_L2)),
  ButtonR1(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_R1)),
  ButtonR2(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_R2)),
  ButtonUp(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_UP)),
  ButtonDown(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_DOWN)),
  ButtonLeft(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_LEFT)),
  ButtonRight(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_RIGHT)),
  ButtonX(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_X)),
  ButtonB(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_B)),
  ButtonY(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_Y)),
  ButtonA(ControlBtn(type, pros::E_CONTROLLER_DIGITAL_A)),
  Axis1(ControlAxis(type, pros::E_CONTROLLER_ANALOG_RIGHT_X)),
  Axis2(ControlAxis(type, pros::E_CONTROLLER_ANALOG_RIGHT_Y)),
  Axis3(ControlAxis(type, pros::E_CONTROLLER_ANALOG_LEFT_Y)),
  Axis4(ControlAxis(type, pros::E_CONTROLLER_ANALOG_LEFT_X)){
  if(type == pros::E_CONTROLLER_MASTER)
    name = "Main Controller";
  else
    name = "Partner Controller";

  gui.addScreen(name);
  gui.addLabel(name, 75, 10, redText, name);
  gui.addLabel(name, 300, 10, redText, "Battery: %d%", (std::function<int()>) std::bind(&Controller::getBatteryCapacity, this));
  // Col 1
  gui.addLabel(name, 10, 45, whiteText, "Button L1: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonL1));
  gui.addLabel(name, 10, 65, whiteText, "Button L2: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonL2));
  gui.addLabel(name, 10, 85, whiteText, "Button Up: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonUp));
  gui.addLabel(name, 10, 105, whiteText, "Button Left: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonLeft));
  gui.addLabel(name, 10, 125, whiteText, "Button Right: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonRight));
  gui.addLabel(name, 10, 145, whiteText, "Button Down: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonDown));
  // Col 2
  gui.addLabel(name, 200, 45, whiteText, "Button R1: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonR1));
  gui.addLabel(name, 200, 65, whiteText, "Button R2: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonR2));
  gui.addLabel(name, 200, 85, whiteText, "Button X: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonX));
  gui.addLabel(name, 200, 105, whiteText, "Button Y: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonY));
  gui.addLabel(name, 200, 125, whiteText, "Button A: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonA));
  gui.addLabel(name, 200, 145, whiteText, "Button B: %b", (std::function<bool()>) std::bind(&ControlBtn::state, &ButtonB));
  // Col 3
  gui.addLabel(name, 370, 45, whiteText, "Axis 1: %d", (std::function<int()>) std::bind(&ControlAxis::getPercent, &Axis1));
  gui.addLabel(name, 370, 65, whiteText, "Axis 2: %d", (std::function<int()>) std::bind(&ControlAxis::getPercent, &Axis2));
  gui.addLabel(name, 370, 85, whiteText, "Axis 3: %d", (std::function<int()>) std::bind(&ControlAxis::getPercent, &Axis3));
  gui.addLabel(name, 370, 105, whiteText, "Axis 4: %d", (std::function<int()>) std::bind(&ControlAxis::getPercent, &Axis4));
  //Bottem
  gui.addButton(name, 0, 160, 200, 150, 20);
  gui.addButtonAction(name, 0, "Go Back", "Home");

  gui.addRelationship(name, (std::function<bool()>)std::bind(&Controller::isConnected, this), "No_Device", true);
  controllerType = type;
}

void Controller::clear(){
  for(int x = 0; x < 3; x++){
    setText(x, 0, "          ");
  }
}

void Controller::clearLine(int line){
  setText(line, 0, "          ");
  pros::delay(50);
}

int Controller::getBatteryCapacity(){
  return pros::c::controller_get_battery_capacity(controllerType);
}

int Controller::getBatteryLevel(){
  return pros::c::controller_get_battery_level(controllerType);
}

bool Controller::isConnected(){
  return pros::c::controller_is_connected(controllerType);
}

void Controller::print(int row, int col, const char* fmt...){
  std::string sum = "";
  va_list args;
  va_start(args, fmt);
  while(*fmt != '\0') {
  	if(*fmt == '%'){
  		++fmt;
  		if(*fmt == 'd'){
  			sum += std::to_string(va_arg(args, int));
        ++fmt;
  		}
  		else if(*fmt == 'f'){
        sum += std::to_string(va_arg(args, double));
        ++fmt;
  		}
  		else if(*fmt == 'c'){
        sum += (char)(va_arg(args, int));
        ++fmt;
  		}
  		else{
	    	++fmt;
	    }
  	}
  	else{
      sum += *fmt;
  		++fmt;
  	}
  }
  va_end(args);
  int n = sum.length();
  char char_array[n + 1];
  strcpy(char_array, sum.c_str());
  pros::c::controller_set_text(controllerType, row, col, char_array);
  pros::delay(50);
}

void Controller::rumble(const char* fmt){
  pros::c::controller_rumble(controllerType, fmt);
  pros::delay(50);
}

void Controller::setText(int row, int col, const char* fmt){
  pros::c::controller_set_text(controllerType, row, col, fmt);
  pros::delay(50);
}

void Controller::callBackCheck(){
  ButtonL1.checkCallBack();
  ButtonL2.checkCallBack();
  ButtonR1.checkCallBack();
  ButtonR2.checkCallBack();
  ButtonUp.checkCallBack();
  ButtonDown.checkCallBack();
  ButtonLeft.checkCallBack();
  ButtonRight.checkCallBack();
  ButtonX.checkCallBack();
  ButtonB.checkCallBack();
  ButtonY.checkCallBack();
  ButtonA.checkCallBack();
}
