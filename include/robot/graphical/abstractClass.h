#include "styles.h"

#ifndef ABSTRACTGUI_H
#define ABSTRACTGUI_H

class AbstractGUI{
protected:
  lv_obj_t* obj1;
  lv_obj_t* obj2;
  bool state = false;
  short xOrgin; //Every thing is in realtion to the upper left coner
  short yOrgin;
  short length;
  short width;
  lv_style_t *style1;
  lv_style_t *style2;
  int mode;

  int* intPointer;
	std::function<int()> intFunction;
	double* doublePointer;
	std::function<double()> doubleFunction;
	bool* boolPointer;
	std::function<bool()> boolFunction;
	std::string* stringPointer;
	std::function<std::string()> stringFunction;
  std::function<lv_style_t*()> lv_styleFunction;

  std::string format[6] = {"Blank", "Blank", "Blank", "Blank", "Blank", "Blank"};
  int actionTime = 0;
};

struct PassInfo{
  std::vector<int> integer;

  std::string string1;
  std::string string2;

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
