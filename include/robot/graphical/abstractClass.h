#include "styles.h"
#include "robot/devices/externalFileClass.h"
#include "robot/devices/timerClass.h"

#ifndef ABSTRACTGUI_H
#define ABSTRACTGUI_H

class AbstractGUI{
protected:
  lv_obj_t* m_obj1;
  lv_obj_t* m_obj2;
  bool m_state = false;
  short m_xOrgin; //Every thing is in realtion to the upper left coner
  short m_yOrgin;
  short m_length;
  short m_width;
  lv_style_t *m_style1;
  lv_style_t *m_style2;
  int m_mode;

  int* m_intPointer;
	std::function<int()> m_intFunction;
	double* m_doublePointer;
	std::function<double()> m_doubleFunction;
	bool* m_boolPointer;
	std::function<bool()> m_boolFunction;
	std::string* m_stringPointer;
	std::function<std::string()> m_stringFunction;
  std::function<lv_style_t*()> m_lv_styleFunction;

  std::string m_format[6] = {"Blank", "Blank", "Blank", "Blank", "Blank", "Blank"};
};

struct PassInfo{
  short xOrgin, yOrgin, length, width;
  int id, mode, rangeLow, rangeHigh, sizeFactor, angle ,numOfDashes, version, passValue;
  std::string text, linkedID, name;

  int* intPointer;
	std::function<int()> intFunction;
	double* doublePointer;
	std::function<double()> doubleFunction;
	bool* boolPointer;
	std::function<bool()> boolFunction;
	std::string* stringPointer;
	std::function<std::string()> stringFunction;
  std::function<lv_style_t*()> lv_styleFunction;

  lv_style_t *style1;
  lv_style_t *style2;

  lv_point_t* points;
};

#endif //ABSTRACTGUI_H
