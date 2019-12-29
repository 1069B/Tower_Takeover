#include "abstractClass.hpp"

#ifndef TOGGLECLASS_H
#define TOGGLECLASS_H

class Screen;

class Toggle: protected AbstractGUI{
public:
  Screen& m_screen;
	Toggle(const PassInfo& p_info, Screen& p_screen);// mode 0

	void draw();

	void update();

	void remove();

  int getState();

  void setState(const bool p_state);
};

#endif // TOGGLECLASS_H
