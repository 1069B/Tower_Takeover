#include "robot/graphical/screenClass.h"

Screen::Screen(PassInfo& info):
m_nextScreenID(*info.stringPointer),
m_version(*info.intPointer){
  m_pageID = info.linkedID;
  m_backGround = info.style1;
  m_btnArray.resize(0); // See about makeing size changes automaticly
}
void Screen::changeBackground(lv_style_t& backColor){
  m_backGround = &backColor;
  lv_obj_set_style(lv_scr_act(), m_backGround);
}

void Screen::addRelationship(std::function<bool()> func, bool inverse, std::string otherScreen){
  m_relation = true;
  m_relatedFunc = func;
  m_relatedScreen = otherScreen;
  m_inversed = inverse;
}
std::string Screen::getRelatedScreen(){
  return m_relatedScreen;
}
std::function<bool()> Screen::getRelatedFunc(){
  return m_relatedFunc;
}
bool Screen::getInverse(){
  return m_inversed;
}
bool Screen::isRelation(){
  return m_relation;
}

void Screen::addButton(PassInfo& info){
  m_btnArray.resize(m_btnArray.size()+1);
	m_btnArray.at(m_btnArray.size()-1) = new Button(info, m_nextScreenID);
}
void Screen::addButtionAction(PassInfo& info){
  for(int y = 0; y < m_btnArray.size(); y++){
    if(m_btnArray[y]->m_id == info.id)
      m_btnArray[y]->defineAction(info);
  }
}
void Screen::addLabel(PassInfo& info){
  m_labelArray.resize(m_labelArray.size()+1);
	m_labelArray.at(m_labelArray.size()-1) = new Label(info);
}
void Screen::addLine(PassInfo& info){
  m_lineArray.resize(m_lineArray.size()+1);
  m_lineArray.at(m_lineArray.size()-1) = new Line(info);
}
void Screen::addMeter(PassInfo& info){
  m_meterArray.resize(m_meterArray.size()+1);
  m_meterArray.at(m_meterArray.size()-1) = new Meter(info);
}
void Screen::addRectangle(PassInfo& info){
  m_rectArray.resize(m_rectArray.size()+1);
  m_rectArray.at(m_rectArray.size()-1) = new Rectangle(info);
}

void Screen::draw(){
  lv_obj_set_style(lv_scr_act(), m_backGround);
  for(int y = 0; y < m_rectArray.size(); y++)
    m_rectArray.at(y)->draw();
  for(int y = 0; y < m_btnArray.size(); y++)
    m_btnArray.at(y)->draw(m_version);

  for(int y = 0; y <m_labelArray.size(); y++)
    m_labelArray.at(y)->draw();

  for(int y = 0; y < m_lineArray.size(); y++)
    m_lineArray.at(y)->draw();

  for(int y = 0; y < m_meterArray.size(); y++)
    m_meterArray.at(y)->draw();
}
void Screen::update(){
  for(int y = 0; y < m_btnArray.size(); y++)
    m_btnArray.at(y)->update(m_version);
  for(int y = 0; y < m_labelArray.size(); y++)
    m_labelArray.at(y)->update();

  for(int y = 0; y < m_meterArray.size(); y++)
    m_meterArray.at(y)->update();
}
void Screen::detect(){
  for(int y = 0; y < m_btnArray.size(); y++)
    m_btnArray.at(y)->checkState(m_version);
}
void Screen::remove(){
  for(int y = 0; y < m_btnArray.size(); y++)
    m_btnArray.at(y)->remove();

  for(int y = 0; y < m_labelArray.size(); y++)
    m_labelArray.at(y)->remove();

  for(int y = 0; y < m_lineArray.size(); y++)
    m_lineArray.at(y)->remove();

  for(int y = 0; y < m_meterArray.size(); y++)
    m_meterArray.at(y)->remove();

  for(int y = 0; y < m_rectArray.size(); y++)
    m_rectArray.at(y)->remove();
}
