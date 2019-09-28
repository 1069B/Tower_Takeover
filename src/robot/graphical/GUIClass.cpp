#include "robot/graphical/GUIClass.hpp"
int noVar = 0;

graphicalInterface::graphicalInterface(const std::string p_startingScreen):m_timer(false), m_GUIStorage("GUI_Storage.txt"){
  if(m_GUIStorage.fileExist() && m_GUIStorage.readBool("Open_Previous")){
    m_nextScreenID = m_GUIStorage.readString("Previous_Screen");
  }
  else{
    m_nextScreenID = p_startingScreen;
  }
  PassInfo info = PassInfo();
  info.linkedID = "Blank";
  info.intPointer = &m_noVersion;
  info.style1 = &defaultBackground;
  info.stringPointer = &m_nextScreenID;
  m_nextScreen = new Screen(info);
  m_currentScreen = new Screen(info);
  m_screenArray.resize(0);
}

void graphicalInterface::addScreen(const std::string p_name, int& p_var){
  addScreen(p_name, p_var, defaultBackground);
}
void graphicalInterface::addScreen(const std::string p_name, lv_style_t& p_backColor){
  addScreen(p_name, m_noVersion, p_backColor);
}
void graphicalInterface::addScreen(const std::string p_name, int& p_var,  lv_style_t&  p_backColor){
  m_screenArray.resize(m_screenArray.size()+1);
  PassInfo info = PassInfo();
  info.name = p_name;
  info.intPointer = &p_var;
  info.style1 = &p_backColor;
  info.stringPointer = &m_nextScreenID;
	m_screenArray.at(m_screenArray.size()-1) = new Screen(info);
}

void graphicalInterface::addButton(const std::string p_screenName, const int p_id, const int p_xOrgin, const int p_yOrgin, const int p_length, const int p_width, int& p_var, lv_style_t& p_btnRel, lv_style_t& p_btnPress){
  PassInfo info = PassInfo();
  info.id = p_id;
  info.xOrgin = p_xOrgin;
  info.yOrgin = p_yOrgin;
  info.length = p_length;
  info.width = p_width;
  info.intPointer = &p_var;
  info.style1= &p_btnRel;
  info.style2= &p_btnPress;
  findScreen(p_screenName)->addButton(info);
}
void graphicalInterface::addButtonAction(const std::string p_screenName, const int p_id, const std::string p_format, const std::string p_linkedID, const int p_btnVer, const int p_value, const int p_mode){
  PassInfo info = PassInfo();
  info.id = p_id;
  info.version = p_btnVer;
  info.passValue = p_value;
  info.mode = p_mode;
  info.text = p_format;
  info.linkedID = p_linkedID;
  findScreen(p_screenName)->addButtionAction(info);
}
void graphicalInterface::addButtonCounter(const std::string p_screenName, const int p_id, const std::string p_format, const int p_btnVer, const int p_btnIncrement){
  addButtonAction(p_screenName, p_id,p_format, p_screenName, p_btnVer, p_btnIncrement, 1);// 1 signals increment mode
}

void graphicalInterface::defineLabel(PassInfo& p_info, const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, const int p_mode){
  p_info.xOrgin = p_xOrgin;
  p_info.yOrgin = p_yOrgin;
  p_info.mode = p_mode;
  p_info.style1 = &p_style;
  p_info.text = p_format;
  findScreen(p_screenName)->addLabel(p_info);
}
void graphicalInterface::addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format){// mode 0
  PassInfo info = PassInfo();
  defineLabel(info, p_screenName, p_xOrgin, p_yOrgin, p_style, p_format, 0);
}
void graphicalInterface::addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, int* p_function){// mode 1
  PassInfo info = PassInfo();
  info.intPointer = p_function;
  defineLabel(info, p_screenName, p_xOrgin, p_yOrgin, p_style, p_format, 1);
}
void graphicalInterface::addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, std::function<int()> p_function){// mode 2
  PassInfo info = PassInfo();
  info.intFunction = p_function;
  defineLabel(info, p_screenName, p_xOrgin, p_yOrgin, p_style, p_format, 2);
}
void graphicalInterface::addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, double* p_function){// mode 3
  PassInfo info = PassInfo();
  info.doublePointer = p_function;
  defineLabel(info, p_screenName, p_xOrgin, p_yOrgin, p_style, p_format, 3);
}
void graphicalInterface::addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, std::function<double()> p_function){// mode 4
  PassInfo info = PassInfo();
  info.doubleFunction = p_function;
  defineLabel(info, p_screenName, p_xOrgin, p_yOrgin, p_style, p_format, 4);

  findScreen(p_screenName)->addLabel(info);
}
void graphicalInterface::addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, bool* p_function){// mode 5
  PassInfo info = PassInfo();
  info.boolPointer = p_function;
  defineLabel(info, p_screenName, p_xOrgin, p_yOrgin, p_style, p_format, 5);
}
void graphicalInterface::addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, std::function<bool()> p_function){// mode 6
  PassInfo info = PassInfo();
  info.boolFunction = p_function;
  defineLabel(info, p_screenName, p_xOrgin, p_yOrgin, p_style, p_format, 6);

  findScreen(p_screenName)->addLabel(info);
}
void graphicalInterface::addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, std::string* p_function){// mode 7
  PassInfo info = PassInfo();
  info.stringPointer = p_function;
  defineLabel(info, p_screenName, p_xOrgin, p_yOrgin, p_style, p_format, 7);
}
void graphicalInterface::addLabel(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, lv_style_t& p_style, const std::string p_format, std::function<std::string()> p_function){// mode 8
  PassInfo info = PassInfo();
  info.stringFunction = p_function;
  defineLabel(info, p_screenName, p_xOrgin, p_yOrgin, p_style, p_format, 8);
}

void graphicalInterface::addLine(const std::string p_screenName, lv_point_t* p_point, lv_style_t& p_style){
  PassInfo info = PassInfo();
  info.points = p_point;
  info.style1 = &p_style;
  findScreen(p_screenName)->addLine(info);
}

void graphicalInterface::addMeter(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, const std::function<int()> p_function, const int p_rangeL, const int p_rangeH, const int p_size, const int p_angle, const int p_numOfDashes, lv_style_t& p_metStyle, lv_style_t& p_textStyle){
  PassInfo info = PassInfo();
  info.xOrgin = p_xOrgin;
  info.yOrgin = p_yOrgin;
  info.rangeLow = p_rangeL;
  info.rangeHigh = p_rangeH;
  info.sizeFactor = p_size;
  info.angle = p_angle;
  info.numOfDashes = p_numOfDashes;
  info.intFunction = p_function;
  info.style1= &p_metStyle;
  info.style2= &p_textStyle;
  findScreen(p_screenName)->addMeter(info);
}
void graphicalInterface::addMeter(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, const std::function<int()> p_function, lv_style_t& p_metStyle, lv_style_t& p_textStyle){
  addMeter(p_screenName, p_xOrgin, p_yOrgin, p_function, 0, 100, 125, 240, 22, p_metStyle, p_textStyle);
}

void graphicalInterface::addRectangle(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, const int p_length, const int p_width, lv_style_t& p_style){
  PassInfo info = PassInfo();
  info.xOrgin = p_xOrgin;
  info.yOrgin = p_yOrgin;
  info.length = p_length;
  info.width = p_width;
  info.mode = false;//mode
  info.style1 = &p_style;
  findScreen(p_screenName)->addRectangle(info);
}
void graphicalInterface::addRectangle(const std::string p_screenName, const int p_xOrgin, const int p_yOrgin, const int p_length, const int p_width, const std::function<lv_style_t*()> background){
  PassInfo info = PassInfo();
  info.xOrgin = p_xOrgin;
  info.yOrgin = p_yOrgin;
  info.length = p_length;
  info.width = p_width;
  info.mode = true;//mode
  info.lv_styleFunction = background;
  findScreen(p_screenName)->addRectangle(info);
}

Screen *graphicalInterface::findScreen(const std::string p_name){
  for(int x = 0; x < m_screenArray.size(); x++){
    if(m_screenArray[x]->m_pageID == p_name){
      return m_screenArray[x];
    }
  }
  return NULL;
}

void graphicalInterface::addRelationship(const std::string p_name, const std::function<bool()> p_function, const std::string p_otherScreen, const bool p_inverse){
  findScreen(p_name)->addRelationship(p_function, p_inverse, p_otherScreen);
}

void graphicalInterface::updateScreen(){
  m_previousScreenID = m_currentScreenID;
  m_currentScreen->remove();
  m_nextScreen = findScreen(m_nextScreenID);
  m_currentScreen = m_nextScreen;
  m_currentScreenID = m_nextScreenID;
  m_currentScreen->draw();
  m_GUIStorage.storeString("Previous_Screen", m_currentScreenID);
}

void graphicalInterface::task(){
  if(m_timer.preformAction() && m_nextScreenID != m_currentScreenID){// Makes the change of screen
    updateScreen();
    m_timer.addActionDelay(400);
  }

  m_currentScreen->detect();

  if(m_timer.preformAction() && m_nextScreenID != m_currentScreenID){// Delay for Visual Button
    m_timer.addActionDelay(100);
  }

  if(m_nextScreen->isRelation() && m_nextScreen->getInverse() && !m_nextScreen->getRelatedFunc()()){
    if(m_currentScreen == findScreen(m_currentScreenID)){
      m_currentScreen->remove();
      m_currentScreen = findScreen(m_nextScreen->getRelatedScreen());
      m_currentScreen->draw();
    }
  }
  else if(m_nextScreen->isRelation() && !m_nextScreen->getInverse() && m_nextScreen->getRelatedFunc()()){
    if(m_currentScreen == findScreen(m_currentScreenID)){
      m_currentScreen->remove();
      m_currentScreen = findScreen(m_nextScreen->getRelatedScreen());
      m_currentScreen->draw();
    }
  }
  else if(m_nextScreen->isRelation() && m_currentScreen != findScreen(m_currentScreenID)){
    m_currentScreen->remove();
    m_currentScreen = findScreen(m_currentScreenID);
    m_currentScreen->draw();
  }

  m_currentScreen->update();
}
