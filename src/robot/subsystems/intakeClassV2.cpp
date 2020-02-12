// #include "robot/subsystems/intakeClassV2.hpp"
// #include "robot/devices/motorClass.hpp"
// #include "robot/graphical/components/alertClass.hpp"
// #include "robotClass.hpp"
//
// IntakeV2::IntakeV2(Robot& p_robot, const std::string p_name): m_robot(p_robot){
//   m_name = p_name;
// }
//
// int IntakeV2::initialize(const std::string p_intakeMotor, const int p_port, const bool p_reversed){
//   if(Motor::findMotor(p_intakeMotor) == NULL)
//     m_intakeMotor = new Motor(p_intakeMotor, p_port, pros::E_MOTOR_GEARSET_18, p_reversed);
//   else
//     m_intakeMotor = Motor::findMotor(p_intakeMotor);
//
//     m_intakeMotor->setBrake(m_brakeMode);
//
//     m_intakeMotor->defineGUI(m_robot.getGUI(), "Home");
//
//     if(m_brakeMode == pros::E_MOTOR_BRAKE_COAST)
//       m_brakeString = "Coast";
//     else if(m_brakeMode == pros::E_MOTOR_BRAKE_BRAKE)
//       m_brakeString = "Brake";
//     else
//       m_brakeString = "Hold";
//
//     defineGUI("Home");
//   return 0;
// }
//
// int IntakeV2::setBrakeMode(const pros::motor_brake_mode_e p_brakeMode){
//   m_brakeMode = p_brakeMode;
//
//   if(m_brakeMode == pros::E_MOTOR_BRAKE_COAST)
//     m_brakeString = "Coast";
//   else if(m_brakeMode == pros::E_MOTOR_BRAKE_BRAKE)
//     m_brakeString = "Brake";
//   else
//     m_brakeString = "Hold";
// }
//
// int IntakeV2::goToVelocity(const int p_velocity){
//   return 0;
// }
//
// int IntakeV2::goToVelocity(const int p_velocity, const Direction p_direction){
//   return 0;
// }
//
// int IntakeV2::goToDuration(const int p_duration, const int p_velocity, const Direction p_direction){
//   return 0;
// }
//
// int IntakeV2::goToPosition(const int p_position, const int p_velocity, const Direction p_direction){
//   return 0;
// }
//
// int IntakeV2::task(){
//   switch ((int)m_mode) {
//     case MANIPULATOR_VELOCITY_DEPENDENT:
//       m_intakeMotor->setVelocity(m_mode);
//       break;
//
//     case MANIPULATOR_TIME_DEPENDENT:
//
//       break;
//
//     case MANIPULATOR_ENCODER_DEPENDENT:
//
//       break;
//
//     case MANIPULATOR_DISABLED:
//       m_intakeMotor -> setVelocity(0);
//       break;
//   }
//   return 0;
// }
//
// int IntakeV2::defineGUI(const  std::string p_returnScreen){
//
//   return 0;
// }
