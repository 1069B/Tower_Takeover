#include "robot/subsystems/baseClass.hpp"
#include "robotClass.hpp"

int Base::initializeHolonomic(std::string p_frontLeftMotor, std::string p_frontRightMotor, std::string p_backLeftMotor, std::string p_backRightMotor){
  if(Motor::findMotor(p_frontLeftMotor) == NULL)
    m_frontLeftMotor = new Motor(p_frontLeftMotor, 1, pros::E_MOTOR_GEARSET_18, true);
  else
    m_frontLeftMotor = Motor::findMotor(p_frontLeftMotor);

  if(Motor::findMotor(p_frontRightMotor) == NULL)
    m_frontRightMotor = new Motor(p_frontRightMotor, 2, pros::E_MOTOR_GEARSET_18, false);
  else
    m_frontRightMotor = Motor::findMotor(p_frontRightMotor);

  if(Motor::findMotor(p_backLeftMotor) == NULL)
    m_backLeftMotor = new Motor(p_backLeftMotor, 3, pros::E_MOTOR_GEARSET_18, true);
  else
    m_backLeftMotor = Motor::findMotor(p_backLeftMotor);

  if(Motor::findMotor(p_backRightMotor) == NULL)
    m_backRightMotor = new Motor(p_backRightMotor, 4, pros::E_MOTOR_GEARSET_18, false);
  else
    m_backRightMotor = Motor::findMotor(p_backRightMotor);
  return 0;
}

int Base::autonomousHolonomic(){
  return 0;
}

int Base::driverHolonomic(){
  if(m_speedUpCurve && m_driftTurning){// Speed Up and Drift Turning
      m_frontLeftVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue()-m_robot.m_mainController.Axis1.getValue());
      m_frontRightVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue()+m_robot.m_mainController.Axis1.getValue());
      m_backLeftVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue()-m_robot.m_mainController.Axis1.getValue());
      m_backRightVelocity =speedUp(m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue()+m_robot.m_mainController.Axis1.getValue());
    }
    else if(m_speedUpCurve && !m_driftTurning){// Speed Up and Point Turning
      if((m_robot.m_mainController.Axis1.getValue()) > 10 || (m_robot.m_mainController.Axis1.getValue()) < -10){// Detects Turning
        m_frontLeftVelocity = speedUp(-m_robot.m_mainController.Axis1.getValue());
        m_frontRightVelocity = speedUp(m_robot.m_mainController.Axis1.getValue());
        m_backLeftVelocity = speedUp(-m_robot.m_mainController.Axis1.getValue());
        m_backRightVelocity = speedUp(m_robot.m_mainController.Axis1.getValue());
      }
      else{//Translational Movement
        m_frontLeftVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue());
        m_frontRightVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue());
        m_backLeftVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue());
        m_backRightVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue());
      }
    }
    else if(!m_speedUpCurve && m_driftTurning){// No Speed Up and Drift Turning
      m_frontLeftVelocity = m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue()-m_robot.m_mainController.Axis1.getValue();
      m_frontRightVelocity = m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue()+m_robot.m_mainController.Axis1.getValue();
      m_backLeftVelocity = m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue()-m_robot.m_mainController.Axis1.getValue();
      m_backRightVelocity = m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue()+m_robot.m_mainController.Axis1.getValue();
    }
    else if(!m_speedUpCurve && !m_driftTurning){// No Speed Up and Point Turning
      if((m_robot.m_mainController.Axis1.getValue()) > 10 || (m_robot.m_mainController.Axis1.getValue()) < -10){// Detects Turning
        m_frontLeftVelocity = -m_robot.m_mainController.Axis1.getValue();
        m_frontRightVelocity = m_robot.m_mainController.Axis1.getValue();
        m_backLeftVelocity = -m_robot.m_mainController.Axis1.getValue();
        m_backRightVelocity = m_robot.m_mainController.Axis1.getValue();
      }
      else{//Translational Movement
        m_frontLeftVelocity = m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue();
        m_frontRightVelocity = m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue();
        m_backLeftVelocity = m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue();
        m_backRightVelocity = m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue();
      }
    }
    else{
      m_frontLeftVelocity = 0;
      m_frontRightVelocity = 0;
      m_backLeftVelocity = 0;
      m_backRightVelocity = 0;
    }

  m_frontRightMotor->setVelocity(m_frontRightVelocity);
  m_frontLeftMotor->setVelocity(m_frontLeftVelocity);
  m_backRightMotor->setVelocity(m_backRightVelocity);
  m_backLeftMotor->setVelocity(m_backLeftVelocity);

  return 0;
}

int Base::disabledHolonomic(){
  m_frontRightMotor->setVelocity(0);
  m_frontLeftMotor->setVelocity(0);
  m_backRightMotor->setVelocity(0);
  m_backLeftMotor->setVelocity(0);
  return 0;
}
