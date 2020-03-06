#include "robotClass.hpp"
#include "robot/devices/motorClass.hpp"
#include "robot/graphical/components/alertClass.hpp"
#include "robot/subsystems/baseComponents/holonomicClass.hpp"

int Robot::baseStop(){
  baseTo(0, 0, 0, 1000);
  return 0;
}

int Robot::baseTo(int speed, int orientation, int turning, int duration){
  m_base.goToVector(speed, orientation, turning);
  robot.task();
  pros::delay(duration);
  m_base.goToVector(0, 0, 0);
  robot.task();
  pros::delay(500);
  return 0;
}

int Robot::autoRed(){
  return 0;
}

int Robot::autoBlue(){
  return 0;
}

int Robot::autoSkills(){
  baseTo(75, 0, 0, 1000); // Cube in Red Small
  baseTo(100, 177, 0, 4500); // Back robot up along wall 1
  baseTo(100, 90, 0, 1500); // Drift away from wall 1 to get second cube
  baseTo(0, 0, 40, 1000); // Angle Robot back towards large red
  baseTo(110, 180, -7, 3100); // Move robot back towards scoring zone
  baseTo(150, 180, 0, 250);// Nudge 2 cubes into large red zone
  baseTo(50, 0, 0, 750);// Forwards away from zone
  baseTo(150, 102, 0, 3000);// Drift towards wall 3 step 1
  baseTo(150, 85, 0, 2250);// Drift towards wall 3 step 2
  baseTo(100, 0, 0, 750);// Shift around two cubes
  baseTo(50, 90, 0, 2000);// Right to wall
  baseTo(125, 180 - 5, 0, 1250);// Forwards into Blue Area
  baseTo(150, 180, 0, 250);// Nudge 2 cubes into large red zone
  baseTo(125, 0 + 2, 0, 3000);
  baseTo(125, 345, 0, 2000);
  baseTo(0, 0, 30, 1000);
  baseTo(200, 0, 0, 2000);
  baseTo(200, 180, 0, 1000);

  return 0;
}
