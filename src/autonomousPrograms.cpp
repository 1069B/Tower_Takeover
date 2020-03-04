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
  return 0;
}

int Robot::autoRed(){
  return 0;
}

int Robot::autoBlue(){
  return 0;
}

int Robot::autoSkills(){
  // Against Wall
  baseTo(25, 90, 0, 1000);
  baseStop();

  // Cube in Blue Small
  baseTo(75, 0, 0, 1000);
  baseStop();

  // Back towards large
  baseTo(125, 174, 0, 3500);
  baseStop();

  // Shift right
  baseTo(75, 270, 0, 2000);
  baseStop();

  // Cube in Angle for 2 greens
  baseTo(0, 0, -50, 750);
  baseStop();

  // Cube in Back two greens
  baseTo(75, 180, 0, 3000);
  baseStop();

  // Cube in Turn
  baseTo(0, 0, 25, 1500);
  baseStop();

  // Robot against Wall
  baseTo(75, 90, 0, 600);
  baseStop();

  // Cube in Large Blue Area
  baseTo(75, 180, 0, 1600);
  baseStop();

  // Robot forward
  baseTo(75, 0, 0, 1200);
  baseStop();

  // Robot align with wall
  baseTo(75, 90, 0, 500);
  baseStop();

// Robot Rotate
  baseTo(0, 0, -25, 1500);
  baseStop();

// Robot drifting towards back wall
  baseTo(125, 270, 8, 2000);
  baseStop();
  // Translate along back wall
  // baseTo(125, 275, 10, 3000);
  // baseStop();

    return 0;

// Back out of red large scoring zone
  m_base.goToVector(75, 90, 0);
  robot.task();
  pros::delay(500);

  baseStop();
  pros::delay(1000);

  m_base.goToVector(150, 345, 0);
  robot.task();
  pros::delay(8000);

  baseStop();
  pros::delay(1000);

  m_base.goToVector(125, 180, 0);
  robot.task();
  pros::delay(1000);

  baseStop();
  //
  // m_base.goToVector(0, 270, 100);
  // m_timer.addActionDelay(1000);
  // robot.task();


  return 0;
}
