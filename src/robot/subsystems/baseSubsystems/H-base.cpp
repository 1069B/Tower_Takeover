#include "robot/subsystems/baseClass.hpp"

int Base::defineHBase(std::string p_backLeftMotor, std::string p_backRightMotor, std::string p_centerMotor){
  if(Motor::findMotor(p_centerMotor) == NULL)
    m_centerMotor = new Motor(p_centerMotor, 1, pros::E_MOTOR_GEARSET_18, false);
  else
    m_centerMotor = Motor::findMotor(p_centerMotor);

  if(Motor::findMotor(p_backLeftMotor) == NULL)
    m_backLeftMotor = new Motor(p_backLeftMotor, 2, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backLeftMotor = Motor::findMotor(p_backLeftMotor);

  if(Motor::findMotor(p_backRightMotor) == NULL)
    m_backRightMotor = new Motor(p_backRightMotor, 3, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backRightMotor = Motor::findMotor(p_backRightMotor);
  return 0;
}
