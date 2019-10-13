#include "main.h"

#ifndef ENCODERCLASS_H
#define ENCODERCLASS_H

class Encoder{
private:
  std::string m_name = "Encoder";
  short m_port;
public:
  int getRotation();

  int defineGUI();
};

#endif // ENCODERCLASS_H
