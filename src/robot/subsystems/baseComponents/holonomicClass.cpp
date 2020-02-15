#include "robot/subsystems/baseComponents/holonomicClass.hpp"
#include "robotClass.hpp"
#include "robot/devices/motorClass.hpp"
#include "robot/graphical/components/alertClass.hpp"

Holonomic::Holonomic(Robot &p_robot, const int p_maximumVelocity):
Base(p_robot, p_maximumVelocity),
m_frontLeftMotor(*Motor::findMotor("FrontLeftMotor", 1, pros::E_MOTOR_GEARSET_18, false)),
m_frontRightMotor(*Motor::findMotor("FrontRightMotor", 2, pros::E_MOTOR_GEARSET_18, true)),
m_backLeftMotor(*Motor::findMotor("BackLeftMotor", 3, pros::E_MOTOR_GEARSET_18, false)),
m_backRightMotor(*Motor::findMotor("BackRightMotor", 4, pros::E_MOTOR_GEARSET_18, true))
{

}

double Holonomic::speedUp(int p_controllerValue){
  double l_a = m_speedUpCoeffiecientA;
	double l_b = m_speedUpCoeffiecientB;
	double l_c = m_speedUpCoeffiecientC;
	double l_h = m_speedUpCoeffiecientH;
  if(p_controllerValue != 0){
    if(p_controllerValue > 5){
      return l_a/(1+(l_a - l_b)/l_b * pow(M_E, (-l_c*(p_controllerValue + l_h))));
    }
    else if(p_controllerValue < -5){
      return -l_a/(1+(l_a - l_b)/l_b * pow(M_E, (l_c*(p_controllerValue - l_h))));
    }
    else
      return 0;
  }
  return 0;
}

int Holonomic::task(){
  if(m_robot.getRobotMode() == ROBOT_DISABLED){

  }
  else if(m_robot.getRobotMode() == ROBOT_OPERATER || m_robot.getRobotMode() == ROBOT_AUTO){
    if(m_baseState == BASE_VECTOR_DEPENDENT){
      m_desiredFrontLeftVelocity = cos(m_motionTranslationAngle/180.0*M_PI) * m_motionTranslationVelocity;
      m_desiredFrontRightVelocity = sin(m_motionTranslationAngle/180.0*M_PI) * m_motionTranslationVelocity;
      m_desiredBackLeftVelocity = sin(m_motionTranslationAngle/180.0*M_PI) * m_motionTranslationVelocity;
      m_desiredBackRightVelocity = cos(m_motionTranslationAngle/180.0*M_PI) * m_motionTranslationVelocity;

      m_desiredFrontLeftVelocity -= m_motionOrientationVelocity;
      m_desiredFrontRightVelocity += m_motionOrientationVelocity;
      m_desiredBackLeftVelocity -= m_motionOrientationVelocity;
      m_desiredBackRightVelocity += m_motionOrientationVelocity;

      m_frontLeftMotor.setVelocity(m_desiredFrontLeftVelocity);
      m_frontRightMotor.setVelocity(m_desiredFrontRightVelocity);
      m_backLeftMotor.setVelocity(m_desiredBackLeftVelocity);
      m_backRightMotor.setVelocity(m_desiredBackRightVelocity);
    }

    if(m_baseState == BASE_DRIVER_DEPENDENT){
      if(m_speedUpCurve && m_driftTurning){// Speed Up and Drift Turning
        m_desiredFrontLeftVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue()+(m_robot.m_mainController.Axis1.getValue()/1.1));
        m_desiredFrontRightVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue()-(m_robot.m_mainController.Axis1.getValue()/1.1));
        m_desiredBackLeftVelocity = speedUp(m_robot.m_mainController.Axis3.getValue()-m_robot.m_mainController.Axis4.getValue()+(m_robot.m_mainController.Axis1.getValue()/1.1));
        m_desiredBackRightVelocity =speedUp(m_robot.m_mainController.Axis3.getValue()+m_robot.m_mainController.Axis4.getValue()-(m_robot.m_mainController.Axis1.getValue()/1.1));
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
  auto &l_gui = m_robot.getGUI();
  //m_armMotor->defineGUI(m_robot.getGUI(), m_name);

  l_gui.addScreen("Holonomic");
  l_gui.addLabel("Holonomic", 200, 10, redText, m_name);
  l_gui.addRectangle("Holonomic", 0, 0, 480, 40, whiteText);

  l_gui.addLabel("Holonomic", 20, 50, whiteText, "Front Left Velocity: %d RPM\t", &m_desiredFrontLeftVelocity);
  l_gui.addLabel("Holonomic", 20, 80, whiteText, "Front Left Velocity: %d RPM\t", &m_desiredFrontRightVelocity);
  l_gui.addLabel("Holonomic", 20, 110, whiteText, "Front Left Velocity: %d RPM\t", &m_desiredBackLeftVelocity);
  l_gui.addLabel("Holonomic", 20, 140, whiteText, "Front Left Velocity: %d RPM\t", &m_desiredBackRightVelocity);

  // l_gui.addButton("Holonomic", m_name+" Motor", 250, 150, 150, 30);
  // l_gui.addButtonScreenChange("Holonomic", m_name+" Motor", m_armMotor->getName());
  //
  // l_gui.addButton("Holonomic", "Next", 250, 200, 150, 30);
  // l_gui.addButtonScreenChange("Holonomic", "Next", m_name+"`");
  //
  // l_gui.addButton("Holonomic", "Back", 40, 200, 150, 30);
  // l_gui.addButtonScreenChange("Holonomic", "Back", "Subsystems");


  /*              Second Screen             */
  // l_gui.addScreen(m_name+"`");
  // l_gui.addLabel(m_name+"`", 200, 10, redText, m_name + "Automation");
  // l_gui.addRectangle(m_name+"`", 0, 0, 480, 40, whiteText);
  //
  // l_gui.addLabel(m_name+"`", 20, 50, whiteText, "In Progess: %b", &m_movementInProgess);
  // l_gui.addLabel(m_name+"`", 20, 75, whiteText, "Start Pos: %d Deg\t", &m_startPosition);
  // l_gui.addLabel(m_name+"`", 20, 100, whiteText, "Current Pos: %d Deg\t", &m_currentPosition);
  // l_gui.addLabel(m_name+"`", 20, 125, whiteText, "End Pos: %d Deg\t", &m_endPosition);
  // l_gui.addLabel(m_name+"`", 20, 150, whiteText, "Direction: %d \t", &m_movementDirection);
  // l_gui.addLabel(m_name+"`", 20, 175, whiteText, "Desired Vel: %d \t", &m_desiredVelcoity);
  //
  // l_gui.addLabel(m_name+"`", 220, 50, whiteText, "Displacement: %d \t", &m_movementDisplacement);
  // l_gui.addLabel(m_name+"`", 220, 75, whiteText, "Up Displacement: %f Deg\t", &m_speedUpDisplacement);
  // l_gui.addLabel(m_name+"`", 220, 100, whiteText, "Up Slope: %f Deg\t", &m_speedUpSlope);
  // l_gui.addLabel(m_name+"`", 220, 125, whiteText, "Down Displacement: %f Deg\t", &m_speedDownDisplacement);
  // l_gui.addLabel(m_name+"`", 220, 150, whiteText, "Down Slope: %f \t", &m_speedDownSlope);
  // l_gui.addLabel(m_name+"`", 220, 175, whiteText, "Mode: %s", &m_movementString);
  //
  // l_gui.addButton(m_name+"`", "Previous", 100, 200, 150, 30);
  // l_gui.addButtonScreenChange(m_name+"`", "Previous", m_name);
  return 0;
}
