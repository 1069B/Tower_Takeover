#include "robot/subsystems/baseClass.hpp"

int Base::initializeTank2(std::string p_backLeftMotor, std::string p_backRightMotor){
  if(Motor::findMotor(p_backLeftMotor) == NULL)
    m_backLeftMotor = new Motor(p_backLeftMotor, 1, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backLeftMotor = Motor::findMotor(p_backLeftMotor);

  if(Motor::findMotor(p_backRightMotor) == NULL)
    m_backRightMotor = new Motor(p_backRightMotor, 2, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backRightMotor = Motor::findMotor(p_backRightMotor);
  return 0;
}

int Base::autonomousTank2(){
  return 0;
}

int Base::driverTank2(){
  return 0;
}
