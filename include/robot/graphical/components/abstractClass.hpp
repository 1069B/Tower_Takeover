#include "../styles.hpp"
#include "robot/devices/externalFileClass.hpp"
#include "robot/devices/timerClass.hpp"

#ifndef ABSTRACTGUI_H
#define ABSTRACTGUI_H

class AbstractGUI{
protected:
  lv_obj_t* m_obj1, *m_obj2;
  bool m_state = false;
  short m_xOrgin, m_yOrgin, m_length, m_width;
  int m_id, m_mode;
  lv_style_t *m_style1, *m_style2;

  int* m_intPointer;
	std::function<int()> m_intFunction;
	double* m_doublePointer;
	std::function<double()> m_doubleFunction;
	bool* m_boolPointer;
	std::function<bool()> m_boolFunction;
	std::string* m_stringPointer;
	std::function<std::string()> m_stringFunction;
  std::function<lv_style_t*()> m_lv_styleFunction;

  std::string m_format = "Blank";
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

  lv_style_t *style1, *style2;
  lv_point_t *points;
};

#endif //ABSTRACTGUI_H
