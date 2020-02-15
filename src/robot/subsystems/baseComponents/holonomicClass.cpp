#include "robot/subsystems/baseComponents/holonomicClass.hpp"
#include "robotClass.hpp"
#include "robot/devices/motorClass.hpp"

Holonomic::Holonomic(Robot &p_robot, const int p_maximumVelocity):
BaseV2(p_robot, p_maximumVelocity),
m_frontLeftMotor(*Motor::findMotor("FrontLeftMotor", 1, pros::E_MOTOR_GEARSET_18, true)),
m_frontRightMotor(*Motor::findMotor("FrontRightMotor", 2, pros::E_MOTOR_GEARSET_18, false)),
m_backLeftMotor(*Motor::findMotor("BackLeftMotor", 3, pros::E_MOTOR_GEARSET_18, true)),
m_backRightMotor(*Motor::findMotor("BackRightMotor", 4, pros::E_MOTOR_GEARSET_18, false))
{

}

int Holonomic::task(){
  if(m_robot.getRobotMode() == ROBOT_DISABLED){

  }
  else if(m_robot.getRobotMode() == ROBOT_OPERATER || m_robot.getRobotMode() == ROBOT_AUTO){
    if(m_baseState == BASE_VECTOR_DEPENDENT){
      m_desiredFrontLeftVelocity = cos((m_motionTranslationAngle * 180)/M_PI) * m_motionTranslationVelocity;
      m_desiredFrontRightVelocity = sin((m_motionTranslationAngle * 180)/M_PI) * m_motionTranslationVelocity;
      m_desiredBackLeftVelocity = sin((m_motionTranslationAngle * 180)/M_PI) * m_motionTranslationVelocity;
      m_desiredBackRightVelocity = cos((m_motionTranslationAngle * 180)/M_PI) * m_motionTranslationVelocity;

      m_frontLeftMotor.setVelocity(m_desiredFrontLeftVelocity);
      m_frontRightMotor.setVelocity(m_desiredFrontRightVelocity);
      m_backLeftMotor.setVelocity(m_desiredBackLeftVelocity);
      m_backRightMotor.setVelocity(m_desiredBackRightVelocity);
    }

    if(m_baseState == BASE_DRIVER_DEPENDENT){
      if(m_speedUpCurve && m_driftTurning){// Speed Up and Drift Turning
        m_desiredFrontLeftVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue()-(m_robot.m_mainController.Axis1.getValue()/2));
        m_desiredFrontRightVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue()+(m_robot.m_mainController.Axis1.getValue()/2));
        m_desiredBackLeftVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue()-(m_robot.m_mainController.Axis1.getValue()/2));
        m_desiredBackRightVelocity =speedUp(m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue()+(m_robot.m_mainController.Axis1.getValue()/2));
      }
      else if(m_speedUpCurve && !m_driftTurning){// Speed Up and Point Turning
        if((m_robot.m_mainController.Axis1.getValue()) > 10 || (m_robot.m_mainController.Axis1.getValue()) < -10){// Detects Turning
          m_desiredFrontLeftVelocity = speedUp(-m_robot.m_mainController.Axis1.getValue());
          m_desiredFrontRightVelocity = speedUp(m_robot.m_mainController.Axis1.getValue());
          m_desiredBackLeftVelocity = speedUp(-m_robot.m_mainController.Axis1.getValue());
          m_desiredBackRightVelocity = speedUp(m_robot.m_mainController.Axis1.getValue());
        }
        else{//Translational Movement
          m_desiredFrontLeftVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue());
          m_desiredFrontRightVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue());
          m_desiredBackLeftVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue());
          m_desiredBackRightVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue());
        }
      }
      else if(!m_speedUpCurve && m_driftTurning){// No Speed Up and Drift Turning
        m_desiredFrontLeftVelocity = m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue()-m_robot.m_mainController.Axis1.getValue();
        m_desiredFrontRightVelocity = m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue()+m_robot.m_mainController.Axis1.getValue();
        m_desiredBackLeftVelocity = m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue()-m_robot.m_mainController.Axis1.getValue();
        m_desiredBackRightVelocity = m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue()+m_robot.m_mainController.Axis1.getValue();
      }
      else if(!m_speedUpCurve && !m_driftTurning){// No Speed Up and Point Turning
        if((m_robot.m_mainController.Axis1.getValue()) > 10 || (m_robot.m_mainController.Axis1.getValue()) < -10){// Detects Turning
          m_desiredFrontLeftVelocity = -m_robot.m_mainController.Axis1.getValue();
          m_desiredFrontRightVelocity = m_robot.m_mainController.Axis1.getValue();
          m_desiredBackLeftVelocity = -m_robot.m_mainController.Axis1.getValue();
          m_desiredBackRightVelocity = m_robot.m_mainController.Axis1.getValue();
        }
        else{//Translational Movement
          m_desiredFrontLeftVelocity = m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue();
          m_desiredFrontRightVelocity = m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue();
          m_desiredBackLeftVelocity = m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue();
          m_desiredBackRightVelocity = m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue();
        }
      }
      else{
        m_desiredFrontLeftVelocity = 0;
        m_desiredFrontRightVelocity = 0;
        m_desiredBackLeftVelocity = 0;
        m_desiredBackRightVelocity = 0;
      }

      m_frontLeftMotor.setVelocity(m_desiredFrontLeftVelocity);
      m_frontRightMotor.setVelocity(m_desiredFrontRightVelocity);
      m_backLeftMotor.setVelocity(m_desiredBackLeftVelocity);
      m_backRightMotor.setVelocity(m_desiredBackRightVelocity);
    }
  }
  return 0;
}

int Holonomic::defineGUI(const std::string p_returnScreen){
  return 0;
}
