#include "robot/varibleDecleration.hpp"
#include "robot/devices/externalFileClass.hpp"
#include "baseClassV2.hpp"

#ifndef HOLONOMICCLASS_H
#define HOLONOMICCLASS_H

class Holonomic:BaseV2{
private:
  Motor& m_frontLeftMotor;
  Motor& m_frontRightMotor;
  Motor& m_backLeftMotor;
  Motor& m_backRightMotor;

  int m_desiredFrontLeftVelocity = 0;
  int m_desiredFrontRightVelocity = 0;
  int m_desiredBackLeftVelocity = 0;
  int m_desiredBackRightVelocity = 0;

  bool m_speedUpCurve = false;
	bool m_driftTurning = false;

  int m_speedUpCoeffiecientA = 201;
	int m_speedUpCoeffiecientB = 5;
	double m_speedUpCoeffiecientC = 0.05;
	int m_speedUpCoeffiecientH = -27;

  double speedUp(int p_controllerValue);

public:
  Holonomic(Robot &p_robot, const int p_maximumVelocity);

  int task();

  int defineGUI(const std::string p_returnScreen);
};

#endif // HOLONOMICCLASS_H
