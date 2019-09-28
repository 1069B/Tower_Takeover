#include "styles.h"
#include "abstractClass.h"

#ifndef LABELCLASS_H
#define LABELCLASS_H

class Label: protected AbstractGUI{
protected:
	friend class Screen;
	Label(const PassInfo& p_info);// mode 0

  void setString();

	void draw();
	void update();
	void remove();
};
#endif // LABELCLASS_H
