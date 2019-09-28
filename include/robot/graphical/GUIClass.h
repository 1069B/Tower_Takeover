#include "screenClass.h"

#ifndef GUICLASS_H
#define GUICLASS_H

extern int noVar;

class graphicalInterface{
private:
  std::vector<Screen*> m_screenArray;
  int m_noVersion = 0;// For screens with only one version
  std::string m_previousScreenID = "A";
  std::string m_currentScreenID = "B";
  std::string m_nextScreenID = "C";
  Screen* m_nextScreen;// = new Screen("Blank", noVersion, defaultBackground, nextScreenID);
  Screen* m_currentScreen;// = new Screen("Blank", noVersion, defaultBackground, nextScreenID);
  Timer m_timer;
  ExternalFile m_GUIStorage;
  void updateScreen();

public:
  graphicalInterface(std::string p_startingScreen="Home");

  void addScreen(std::string p_name, int& p_var);
  void addScreen(std::string p_name, lv_style_t& p_backColor = defaultBackground);
  void addScreen(std::string p_name, int& p_var, lv_style_t& p_backColor);

  void addRelationship(std::string p_name, std::function<bool()> p_func, std::string p_otherScreen, bool p_inverse = false);

  Screen *findScreen(std::string p_name);

  void addButton(std::string p_screenName, int p_id, int p_xOrgin, int p_yOrgin, int p_length, int p_width, int& p_var=noVar, lv_style_t& p_btnRel=defaultBtnRel, lv_style_t& p_btnPress=defaultBtnPress);
	void addButtonAction(std::string p_screenName, int p_id, std::string p_format, std::string p_linkedID, int p_btnVer=0, int p_value=0, int p_mode=0);
  void addButtonCounter(std::string p_screenName, int p_id, std::string p_format, int p_btnVer=0, int p_btnIncrement=1);

  void defineLabel(PassInfo& p_info, std::string p_screenName, int p_xOrgin, int p_yOrgin, lv_style_t& p_style, std::string p_format, int p_mode);
  void addLabel(std::string p_screenName, int p_xOrgin, int p_yOrgin, lv_style_t& p_style, std::string p_format);// mode 0
  void addLabel(std::string p_screenName, int p_xOrgin, int p_yOrgin, lv_style_t& p_style, std::string p_format, int* p_function);// mode 1
	void addLabel(std::string p_screenName, int p_xOrgin, int p_yOrgin, lv_style_t& p_style, std::string p_format, std::function<int()> p_function);// mode 2
	void addLabel(std::string p_screenName, int p_xOrgin, int p_yOrgin, lv_style_t& p_style, std::string p_format, double* p_function);// mode 3
	void addLabel(std::string p_screenName, int p_xOrgin, int p_yOrgin, lv_style_t& p_style, std::string p_format, std::function<double()> p_function);// mode 4
	void addLabel(std::string p_screenName, int p_xOrgin, int p_yOrgin, lv_style_t& p_style, std::string p_format, bool* p_function);// mode 5
	void addLabel(std::string p_screenName, int p_xOrgin, int p_yOrgin, lv_style_t& p_style, std::string p_format, std::function<bool()> p_function);// mode 6
	void addLabel(std::string p_screenName, int p_xOrgin, int p_yOrgin, lv_style_t& p_style, std::string p_format, std::string* p_function);// mode 7
	void addLabel(std::string p_screenName, int p_xOrgin, int p_yOrgin, lv_style_t& p_style, std::string p_format, std::function<std::string()> p_function);// mode 8

  void addLine(std::string p_screenName, lv_point_t* p_point, lv_style_t& p_style = whiteText);

  void addMeter(std::string p_screenName, int p_xOrgin, int p_yOrgin, std::function<int()> p_function, int p_rangeL=0, int p_rangeH=100, int p_size=125, int p_angle=240, int p_numOfDashes=22, lv_style_t& p_metStyle=meterStyle, lv_style_t& p_textStyle=whiteText);
  void addMeter(std::string p_screenName, int p_xOrgin, int p_yOrgin, std::function<int()> p_function, lv_style_t& p_metStyle=meterStyle, lv_style_t& p_textStyle=whiteText);

  void addRectangle(std::string p_screenName, int p_xOrgin, int p_yOrgin, int p_length, int p_width, lv_style_t& p_style);
  void addRectangle(std::string p_screenName, int p_xOrgin, int p_yOrgin, int p_length, int p_width, std::function<lv_style_t*()> p_background);

  void task();
};

extern graphicalInterface gui;

#endif // GUICLASS_H
