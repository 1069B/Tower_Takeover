#include "abstractClass.hpp"

#ifndef BUTTONCLASS_H
#define BUTTONCLASS_H

class Screen;

class Button: protected AbstractGUI{
public:
  friend class Screen;
  Screen& m_screen;
  std::string& m_nextScreenVar;
  std::string m_linkedScreenID = "None";
  bool m_changeVar = false;
  bool m_incrementVar = false;
  bool m_changeScreen = false;
  bool m_changeBackground = false;
  int m_value = 0;
  Timer m_timer;

  Button(const PassInfo& p_info, Screen& p_screen);

  void defineAction(const PassInfo& p_info);

  void checkState();

  bool returnState();

  void draw();
  void update();
  void remove();
};

#endif // BUTTONCLASS_H
