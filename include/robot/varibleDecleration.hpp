#include "main.h"
#include "graphical/styles.hpp"

#ifndef ENUMS_H
#define ENUMS_H

enum RobotMode{
    ROBOT_AUTO = 0,
    ROBOT_OPERATER = 1,
    ROBOT_DISABLED = 2
};

enum TaskMode{
    TASK_AUTO = 0,
    TASK_OPERATER = 1,
    TASK_DISABLED = 2
};

enum TaskType{
    TASK_DURING_AUTO = 0,
    TASK_DURING_OPERATER = 1,
    TASK_ALWAYS = 2
};

enum ManipulatorMode {
  MANIPULATOR_VELOCITY_DEPENDENT = 0,
  MANIPULATOR_TIME_DEPENDENT = 1,
  MANIPULATOR_ENCODER_DEPENDENT = 2,
  MANIPULATOR_DISABLED = 3
};

enum BaseType {
	HOLONOMIC = 0,
	HBASE = 1,
	MECANUM = 2,
	TANK2 = 3,
	TANK4 = 4
};

enum BaseMode {
	NO_CORECTIONS = 0,
	ACTIVE_CORRECTIONS = 1,
};

enum AutonomousSide{
  AUTO_BLUE = 0,
  AUTO_RED = 1,
  AUTO_SKILLS = 2,
  AUTO_NONE = 3
};

class ControlAxis;
class ControlBtn;
class Controller;

class Encoder;
class ExternalFile;
class Motor;

struct SubTask;
class TaskScheduler;
class Timer;

struct PassInfo;
class Alert;
class Button;
class Label;
class Line;
class Meter;
class Rectangle;
class Toggle;

class Screen;
class GraphicalInterface;

struct PortSelector;

class Arm;
class Base;
class Intake;
class Odometry;

struct AutoBaseEvent;
struct AutoArmEvent;
struct AutoIntakeEvent;

class AutoProgram;
class Autonomous;

class Robot;

extern Alert g_alert;

extern Robot robot;

#endif // ENUMS_H
