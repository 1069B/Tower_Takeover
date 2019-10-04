#include "robot/graphical/screenClass.hpp"

Screen::Screen(const PassInfo& p_info):
m_nextScreenID(*p_info.stringPointer),
m_version(*p_info.intPointer){
  m_pageID = p_info.linkedID;
  m_backGround = p_info.style1;
}
void Screen::changeBackground(lv_style_t& p_backColor){
  m_backGround = &p_backColor;
  lv_obj_set_style(lv_scr_act(), m_backGround);
}

void Screen::addRelationship(const std::function<bool()> func, const bool inverse, const std::string otherScreen){
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

void Screen::addButton(const PassInfo& p_info){
  m_btnArray.resize(m_btnArray.size()+1);
	m_btnArray.at(m_btnArray.size()-1) = new Button(p_info, m_nextScreenID);
}
void Screen::addButtionAction(const PassInfo& p_info){
  for(int y = 0; y < m_btnArray.size(); y++){
    if(m_btnArray.at(y)->m_id == p_info.id)
      m_btnArray.at(y)->defineAction(p_info);
  }
}
void Screen::addLabel(const PassInfo& p_info){
  m_labelArray.resize(m_labelArray.size()+1);
	m_labelArray.at(m_labelArray.size()-1) = new Label(p_info);
}
void Screen::addLine(const PassInfo& p_info){
  m_lineArray.resize(m_lineArray.size()+1);
  m_lineArray.at(m_lineArray.size()-1) = new Line(p_info);
}
void Screen::addMeter(const PassInfo& p_info){
  m_meterArray.resize(m_meterArray.size()+1);
  m_meterArray.at(m_meterArray.size()-1) = new Meter(p_info);
}
void Screen::addRectangle(const PassInfo& p_info){
  m_rectArray.resize(m_rectArray.size()+1);
  m_rectArray.at(m_rectArray.size()-1) = new Rectangle(p_info);
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
