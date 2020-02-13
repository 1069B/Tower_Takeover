#include "robot/subsystems/intakeClassV2.hpp"
#include "robot/devices/motorClass.hpp"
#include "robot/graphical/components/alertClass.hpp"
#include "robotClass.hpp"

IntakeV2::IntakeV2(Robot& p_robot, const std::string p_name): m_robot(p_robot){
  m_name = p_name;
}

int IntakeV2::initialize(const std::string p_intakeMotor, const int p_port, const int p_maximumVelcouty, const bool p_reversed){
  if(Motor::findMotor(p_intakeMotor) == NULL)
    m_intakeMotor = new Motor(p_intakeMotor, p_port, pros::E_MOTOR_GEARSET_18, p_reversed);
  else
    m_intakeMotor = Motor::findMotor(p_intakeMotor);

    m_intakeMotor->setBrake(m_brakeMode);

    m_intakeMotor->defineGUI(m_robot.getGUI(), "Home");

    if(m_brakeMode == pros::E_MOTOR_BRAKE_COAST)
      m_brakeString = "Coast";
    else if(m_brakeMode == pros::E_MOTOR_BRAKE_BRAKE)
      m_brakeString = "Brake";
    else
      m_brakeString = "Hold";

    m_maximumVelocity = p_maximumVelcouty;

    defineGUI("Home");
  return 0;
}

int IntakeV2::setBrakeMode(const pros::motor_brake_mode_e p_brakeMode){
  m_brakeMode = p_brakeMode;

  if(m_brakeMode == pros::E_MOTOR_BRAKE_COAST)
    m_brakeString = "Coast";
  else if(m_brakeMode == pros::E_MOTOR_BRAKE_BRAKE)
    m_brakeString = "Brake";
  else
    m_brakeString = "Hold";

  return 0;
}

int IntakeV2::goToVelocity(const int p_velocity){
  if(!m_movementInProgess){
    if(m_mode == MANIPULATOR_TOGGLE_FORWARD || m_mode == MANIPULATOR_TOGGLE_FORWARD){
      if(abs(p_velocity) < 5)
        return 0;
    }

    if(m_maximumVelocity < p_velocity)
      m_desiredVelocity = abs(m_maximumVelocity);
    else
      m_desiredVelocity = abs(p_velocity);

    if(m_desiredVelocity == 0)
      m_desiredDirection = DIRECTION_STATIONARY;
    else{
      if(m_desiredVelocity/abs(m_desiredVelocity) == 1)
        m_desiredDirection = DIRECTION_FORWARD;
      else if(m_desiredVelocity/abs(m_desiredVelocity) == -1)
        m_desiredDirection = DIRECTION_BACKWARDS;
    }
    m_mode = MANIPULATOR_VELOCITY_DEPENDENT;
  }
  return 0;
}

int IntakeV2::goToVelocity(const int p_velocity, const Direction p_direction){
  if(!m_movementInProgess){
    if(m_mode == MANIPULATOR_TOGGLE_FORWARD || m_mode == MANIPULATOR_TOGGLE_FORWARD){
      if(abs(p_velocity) < 5)
        return 0;
    }

    if(m_maximumVelocity < p_velocity)
      m_desiredVelocity = abs(m_maximumVelocity);
    else
      m_desiredVelocity = abs(p_velocity);

    m_desiredDirection = p_direction;
    m_mode = MANIPULATOR_VELOCITY_DEPENDENT;
  }
  return 0;
}

int IntakeV2::goToDuration(const int p_duration, const int p_velocity, const Direction p_direction){
  if(m_maximumVelocity < p_velocity)
    m_desiredVelocity = abs(m_maximumVelocity);
  else
    m_desiredVelocity = abs(p_velocity);

  m_desiredDirection = p_direction;

  m_timer.addActionDelay(p_duration);
  m_mode = MANIPULATOR_TIME_DEPENDENT;
  m_movementInProgess = true;
  return 0;
}

int IntakeV2::goToPosition(const int p_position, const int p_velocity, const Direction p_direction){
  /*Do Later Not Needed for Tower Takeover*/
  m_mode = MANIPULATOR_ENCODER_DEPENDENT;
  return 0;
}

int IntakeV2::toggleForward(){
  if(m_mode != MANIPULATOR_TOGGLE_FORWARD)
    m_mode = MANIPULATOR_TOGGLE_FORWARD;
  else
    m_mode = MANIPULATOR_DISABLED;
  return 0;
}

int IntakeV2::toggleBackward(){
  if(m_mode != MANIPULATOR_TOGGLE_BACKWARD)
    m_mode = MANIPULATOR_TOGGLE_BACKWARD;
  else
    m_mode = MANIPULATOR_DISABLED;
  return 0;
}

int IntakeV2::task(){
  switch ((int)m_mode) {
    case MANIPULATOR_VELOCITY_DEPENDENT:
      m_intakeMotor->setVelocity(m_desiredVelocity);
      break;

    case MANIPULATOR_TIME_DEPENDENT:
      if(m_timer.preformAction()){
        m_intakeMotor->setVelocity(0);
        m_movementInProgess = false;
      }
      else{
        m_intakeMotor->setVelocity(m_desiredVelocity);
      }
      break;

    case MANIPULATOR_ENCODER_DEPENDENT:
      /*
      Doesn't Need to Be Done Yet :) Do over the summer
      Be able to rotate to a position along the intake
      */
      break;

    case MANIPULATOR_TOGGLE_FORWARD:
      m_intakeMotor->setVelocity(m_maximumVelocity * DIRECTION_FORWARD);
      break;

    case MANIPULATOR_TOGGLE_BACKWARD:
      m_intakeMotor->setVelocity(m_maximumVelocity * DIRECTION_BACKWARDS);
      break;

    case MANIPULATOR_DISABLED:
      m_intakeMotor->setVelocity(0);
      break;
  }
  return 0;
}

int IntakeV2::defineGUI(const std::string p_returnScreen){
  auto &l_gui = m_robot.getGUI();
  m_intakeMotor->defineGUI(m_robot.getGUI(), m_name);

  l_gui.addScreen(m_name);
  l_gui.addLabel(m_name, 200, 10, redText, m_name);
  l_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  l_gui.addLabel(m_name, 20, 50, whiteText, "Current Position: %d Deg   ", &m_currentPosition);
  l_gui.addLabel(m_name, 20, 80, whiteText, "Desired Velocity: %d RPM   ", &m_desiredVelocity);
  //l_gui.addLabel(m_name, 20, 110, whiteText, "Arm Mode: %s", &m_modeString);
  l_gui.addLabel(m_name, 20, 140, whiteText, "Brake Mode: %s", &m_brakeString);
  //l_gui.addLabel(m_name, 20, 170, whiteText, "Reversed: %b", &m_reversed);

  l_gui.addButton(m_name, m_name+" Motor", 250, 150, 150, 30);
  l_gui.addButtonScreenChange(m_name, m_name+" Motor", m_intakeMotor->getName());

  l_gui.addButton(m_name, "Next", 250, 200, 150, 30);
  l_gui.addButtonScreenChange(m_name, "Next", m_name+"`");

  l_gui.addButton(m_name, "Back", 40, 200, 150, 30);
  l_gui.addButtonScreenChange(m_name, "Back", "Subsystems");


  /*              Second Screen             */
  l_gui.addScreen(m_name+"`");
  l_gui.addLabel(m_name+"`", 200, 10, redText, m_name + "Automation");
  l_gui.addRectangle(m_name+"`", 0, 0, 480, 40, whiteText);

  l_gui.addLabel(m_name+"`", 20, 50, whiteText, "In Progess: %b", &m_movementInProgess);
  l_gui.addLabel(m_name+"`", 20, 75, whiteText, "Start Pos: %d Deg\t", &m_startPosition);
  l_gui.addLabel(m_name+"`", 20, 100, whiteText, "Current Pos: %d Deg\t", &m_currentPosition);
  l_gui.addLabel(m_name+"`", 20, 125, whiteText, "End Pos: %d Deg\t", &m_endPosition);
  //l_gui.addLabel(m_name+"`", 20, 150, whiteText, "Direction: %d \t", &m_movementDirection);
  l_gui.addLabel(m_name+"`", 20, 175, whiteText, "Desired Vel: %d \t", &m_desiredVelocity);

  l_gui.addLabel(m_name+"`", 220, 50, whiteText, "Displacement: %d \t", &m_movementDisplacement);
  // l_gui.addLabel(m_name+"`", 220, 75, whiteText, "Up Displacement: %f Deg\t", &m_speedUpDisplacement);
  // l_gui.addLabel(m_name+"`", 220, 100, whiteText, "Up Slope: %f Deg\t", &m_speedUpSlope);
  // l_gui.addLabel(m_name+"`", 220, 125, whiteText, "Down Displacement: %f Deg\t", &m_speedDownDisplacement);
  // l_gui.addLabel(m_name+"`", 220, 150, whiteText, "Down Slope: %f \t", &m_speedDownSlope);
  l_gui.addLabel(m_name+"`", 220, 175, whiteText, "Mode: %s", &m_movementString);

  l_gui.addButton(m_name+"`", "Previous", 100, 200, 150, 30);
  l_gui.addButtonScreenChange(m_name+"`", "Previous", m_name);
  return 0;
}
