#include "robot/subsystems/armClassV2.hpp"
#include "robotClass.hpp"

ArmV2::ArmV2(Robot& p_robot) : m_robot(p_robot){

}

int ArmV2::task(){
  switch (m_robot.getRobotMode()) {
    case /* value */:
  }
  return 0;
}
