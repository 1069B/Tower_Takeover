#include "robot/graphical/GUIClass.h"
int noVar = 0;

graphicalInterface::graphicalInterface(std::string startingScreen):timer(false), GUIStorage("GUI_Storage.txt"){
  if(GUIStorage.fileExist() && GUIStorage.readBool("Open_Previous")){
    nextScreenID = GUIStorage.readString("Previous_Screen");
  }
  else{
    nextScreenID = startingScreen;
  }
  PassInfo info = PassInfo();
  info.string1 = "Blank";
  info.intPointer = &noVersion;
  info.style1 = &defaultBackground;
  info.stringPointer = &nextScreenID;
  nextScreen = new Screen(info);
  currentScreen = new Screen(info);
  screenArray.resize(0);
}

void graphicalInterface::addScreen(std::string name, int& var){
  addScreen(name, var, defaultBackground);
}
void graphicalInterface::addScreen(std::string name, lv_style_t& backColor){
  addScreen(name, noVersion, backColor);
}
void graphicalInterface::addScreen(std::string name, int& var, lv_style_t& backColor){
  screenArray.resize(screenArray.size()+1);
  PassInfo info = PassInfo();
  info.string1 = name;
  info.intPointer = &var;
  info.style1 = &backColor;
  info.stringPointer = &nextScreenID;
	screenArray.at(screenArray.size()-1) = new Screen(info);
}

void graphicalInterface::addButton(std::string screenName, int id, int xOrg, int yOrg, int len, int wid, int& var, lv_style_t& btnRel, lv_style_t& btnPress){
  PassInfo info = PassInfo();
  info.id = id;
  info.xOrgin = xOrg;
  info.yOrgin = yOrg;
  info.length = len;
  info.width = wid;
  info.intPointer = &var;
  info.style1= &btnRel;
  info.style2= &btnPress;
  findScreen(screenName)->addButton(info);
}
void graphicalInterface::addButtonAction(std::string screenName, int id, std::string theText, std::string linkedID, int btnVer, int val, int mode){
  PassInfo info = PassInfo();
  info.integer.resize(4);
  info.integer.at(0) = id;
  info.integer.at(1) = btnVer;
  info.integer.at(2) = val;
  info.integer.at(3) = mode;
  info.string1 = theText;
  info.string2 = linkedID;
  findScreen(screenName)->addButtionAction(info);
}
void graphicalInterface::addButtonCounter(std::string screenName, int id, std::string theText, int btnVer, int btnIncrement){
  addButtonAction(screenName, id, theText, screenName, btnVer, btnIncrement, 1);// 1 signals increment mode
}

void graphicalInterface::defineLabel(PassInfo& info, std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, int mode){
  info.integer.resize(3);
  info.xOrgin = xOrg;
  info.yOrgin = yOrg;
  info.integer.at(2) = mode;
  info.style1 = &style;
  info.string1 = fmt;
  findScreen(screenName)->addLabel(info);
}
void graphicalInterface::addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt){// mode 0
  PassInfo info = PassInfo();
  defineLabel(info, screenName, xOrg, yOrg, style, fmt, 0);
}
void graphicalInterface::addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, int* var){// mode 1
  PassInfo info = PassInfo();
  info.intPointer = var;
  defineLabel(info, screenName, xOrg, yOrg, style, fmt, 1);
}
void graphicalInterface::addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, std::function<int()> var){// mode 2
  PassInfo info = PassInfo();
  info.intFunction = var;
  defineLabel(info, screenName, xOrg, yOrg, style, fmt, 2);
}
void graphicalInterface::addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, double* var){// mode 3
  PassInfo info = PassInfo();
  info.doublePointer = var;
  defineLabel(info, screenName, xOrg, yOrg, style, fmt, 3);
}
void graphicalInterface::addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, std::function<double()> var){// mode 4
  PassInfo info = PassInfo();
  info.doubleFunction = var;
  defineLabel(info, screenName, xOrg, yOrg, style, fmt, 4);

  findScreen(screenName)->addLabel(info);
}
void graphicalInterface::addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, bool* var){// mode 5
  PassInfo info = PassInfo();
  info.boolPointer = var;
  defineLabel(info, screenName, xOrg, yOrg, style, fmt, 5);
}
void graphicalInterface::addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, std::function<bool()> var){// mode 6
  PassInfo info = PassInfo();
  info.boolFunction = var;
  defineLabel(info, screenName, xOrg, yOrg, style, fmt, 6);

  findScreen(screenName)->addLabel(info);
}
void graphicalInterface::addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, std::string* var){// mode 7
  PassInfo info = PassInfo();
  info.stringPointer = var;
  defineLabel(info, screenName, xOrg, yOrg, style, fmt, 7);
}
void graphicalInterface::addLabel(std::string screenName, int xOrg, int yOrg, lv_style_t& style, std::string fmt, std::function<std::string()> var){// mode 8
}

void graphicalInterface::addLine(std::string screenName, lv_point_t* point, lv_style_t& theStyle){
  PassInfo info = PassInfo();
  info.points = point;
  info.style1 = &theStyle;
  findScreen(screenName)->addLine(info);
}

void graphicalInterface::addMeter(std::string screenName, int xOrg, int yOrg, std::function<int()> func, int rangeL, int rangeH, int theSize, int theAngle, int numOfDashes, lv_style_t& metStyle, lv_style_t& textStyle){
  PassInfo info = PassInfo();
  info.integer.resize(7);
  info.xOrgin = xOrg;
  info.yOrgin = yOrg;
  info.integer.at(2) = rangeL;
  info.integer.at(3) = rangeH;
  info.integer.at(4) = theSize;
  info.integer.at(5) = theAngle;
  info.integer.at(6) = numOfDashes;
  info.intFunction = func;
  info.style1= &metStyle;
  info.style2= &textStyle;
  findScreen(screenName)->addMeter(info);
}
void graphicalInterface::addMeter(std::string screenName, int xOrg, int yOrg, std::function<int()> func, lv_style_t& metStyle, lv_style_t& textStyle){
  addMeter(screenName, xOrg, yOrg, func, 0, 100, 125, 240, 22, metStyle, textStyle);
}

void graphicalInterface::addRectangle(std::string screenName, int xOrg, int yOrg, int len, int wid, lv_style_t& style){
  PassInfo info = PassInfo();
  info.integer.resize(5);
  info.xOrgin = xOrg;
  info.yOrgin = yOrg;
  info.length = len;
  info.width = wid;
  info.integer.at(4) = false;//mode
  info.style1 = &style;
  findScreen(screenName)->addRectangle(info);
}
void graphicalInterface::addRectangle(std::string screenName, int xOrg, int yOrg, int len, int wid, std::function<lv_style_t*()> background){
  PassInfo info = PassInfo();
  info.integer.resize(5);
  info.xOrgin = xOrg;
  info.yOrgin = yOrg;
  info.length = len;
  info.width = wid;
  info.integer.at(4) = true;//mode
  info.lv_styleFunction = background;
  findScreen(screenName)->addRectangle(info);
}

Screen *graphicalInterface::findScreen(std::string name){
  for(int x = 0; x < screenArray.size(); x++){
    if(screenArray[x]->pageID == name){
      return screenArray[x];
    }
  }
  return NULL;
}

void graphicalInterface::addRelationship(std::string name, std::function<bool()> func, std::string otherScreen, bool inverse){
  findScreen(name)->addRelationship(func, inverse, otherScreen);
}

void graphicalInterface::updateScreen(){
  previousScreenID = currentScreenID;
  currentScreen->remove();
  nextScreen = findScreen(nextScreenID);
  currentScreen = nextScreen;
  currentScreenID = nextScreenID;
  currentScreen->draw();
  GUIStorage.storeString("Previous_Screen", currentScreenID);
}

void graphicalInterface::task(){
  if(timer.preformAction() && nextScreenID != currentScreenID){// Makes the change of screen
    updateScreen();
    timer.addActionDelay(400);
  }

  currentScreen->detect();

  if(timer.preformAction() && nextScreenID != currentScreenID){// Delay for Visual Button
    timer.addActionDelay(100);
  }

  if(nextScreen->isRelation() && nextScreen->getInverse() && !nextScreen->getRelatedFunc()()){
    if(currentScreen == findScreen(currentScreenID)){
      currentScreen->remove();
      currentScreen = findScreen(nextScreen->getRelatedScreen());
      currentScreen->draw();
    }
  }
  else if(nextScreen->isRelation() && !nextScreen->getInverse() && nextScreen->getRelatedFunc()()){
    if(currentScreen == findScreen(currentScreenID)){
      currentScreen->remove();
      currentScreen = findScreen(nextScreen->getRelatedScreen());
      currentScreen->draw();
    }
  }
  else if(nextScreen->isRelation() && currentScreen != findScreen(currentScreenID)){
    currentScreen->remove();
    currentScreen = findScreen(currentScreenID);
    currentScreen->draw();
  }

  currentScreen->update();
}
