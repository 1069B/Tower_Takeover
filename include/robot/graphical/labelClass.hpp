#include "styles.hpp"
#include "abstractClass.hpp"

#ifndef LABELCLASS_H
#define LABELCLASS_H

class Screen;

class Label: protected AbstractGUI{
public:
  Screen& m_screen;
	Label(const PassInfo& p_info, Screen& p_screen);// mode 0

  void setString();

	void draw();
	void update();
	void remove();
};
#endif // LABELCLASS_H
