#include "screenClass.h"

#ifndef GUICLASS_H
#define GUICLASS_H

extern int noVar;

class graphicalInterface{
private:
  std::vector<Screen*> screenArray;
  int actionTime = 0;
  int noVersion = 0;// For screens with only one version
  std::string previousScreenID = "Blank";
  std::string currentScreenID = "Blank";
  std::string nextScreenID = "Home";
  Screen* nextScreen;// = new Screen("Blank", noVersion, defaultBackground, nextScreenID);
  Screen* currentScreen;// = new Screen("Blank", noVersion, defaultBackground, nextScreenID);

  void updateScreen();

public:
  graphicalInterface(std::string startingScreen="Home");

  void addScreen(std::string name, int& var);
  void addScreen(std::string name, lv_style_t& backColor = defaultBackground);
  void addScreen(std::string name, int& var, lv_style_t& backColor);

  void addRelationship(std::string name, std::function<bool()> func, std::string otherScreen, bool inverse = false);

  Screen *findScreen(std::string name);

  void addButton(std::string screenName, int id, int xOrg, int yOrg, int len, int wid, int& var=noVar, lv_style_t& btnRel=defaultBtnRel, lv_style_t& btnPress=defaultBtnPress);
	void addButtonAction(std::string screenName, int id, std::string theText, std::string linkedID, int btnVer=0, int val=0, int mode=0);
  void addButtonCounter(std::string screenName, int id, std::string theText, int btnVer=0, int btnIncrement=1);

  void defineLabel(PassInfo& info, std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, int mode);
  void addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt);// mode 0
  void addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, int* var);// mode 1
	void addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, std::function<int()> var);// mode 2
	void addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, double* var);// mode 3
	void addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, std::function<double()> var);// mode 4
	void addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, bool* var);// mode 5
	void addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, std::function<bool()> var);// mode 6
	void addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, std::string* var);// mode 7
	void addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, std::function<std::string()> var);// mode 8

  void addLine(std::string screenName, lv_point_t* point, lv_style_t& theStyle = whiteText);

  void addMeter(std::string screenName, int xOrg, int yOrg, std::function<int()> func, int rangeL=0, int rangeH=100, int theSize=125, int theAngle=240, int numOfDashes=22, lv_style_t& metStyle=meterStyle, lv_style_t& textStyle=whiteText);
  void addMeter(std::string screenName, int xOrg, int yOrg, std::function<int()> func, lv_style_t& metStyle=meterStyle, lv_style_t& textStyle=whiteText);

  void addRectangle(std::string screenName, int xOrg, int yOrg, int len, int wid, lv_style_t& style);
  void addRectangle(std::string screenName, int xOrg, int yOrg, int len, int wid, std::function<lv_style_t*()> background);

  void task();
};

extern graphicalInterface gui;

#endif // GUICLASS_H
