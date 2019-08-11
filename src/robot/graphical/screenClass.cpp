#include "robot/graphical/screenClass.h"

Screen::Screen(PassInfo& info):
nextScreenID(*info.stringPointer),
version(*info.intPointer){
  pageID = info.string1;
  backGround = info.style1;
  btnArray.resize(0); // See about makeing size changes automaticly
}
void Screen::changeBackground(lv_style_t& backColor){
  backGround = &backColor;
  lv_obj_set_style(lv_scr_act(), backGround);
}

void Screen::addRelationship(std::function<bool()> func, bool inverse, std::string otherScreen){
  relation = true;
  relatedFunc = func;
  relatedScreen = otherScreen;
  inversed = inverse;
}
std::string Screen::getRelatedScreen(){
  return relatedScreen;
}
std::function<bool()> Screen::getRelatedFunc(){
  return relatedFunc;
}
bool Screen::getInverse(){
  return inversed;
}
bool Screen::isRelation(){
  return relation;
}

void Screen::addButton(PassInfo& info){
  btnArray.resize(btnArray.size()+1);
	btnArray.at(btnArray.size()-1) = new Button(info, nextScreenID);
}
void Screen::addButtionAction(PassInfo& info){
  for(int y = 0; y < btnArray.size(); y++){
    if(btnArray[y]->id == info.integer.at(0))
      btnArray[y]->defineAction(info);
  }
}
void Screen::addLabel(PassInfo& info){
  labelArray.resize(labelArray.size()+1);
	labelArray.at(labelArray.size()-1) = new Label(info);
}
void Screen::addLine(PassInfo& info){
  lineArray.resize(lineArray.size()+1);
  lineArray.at(lineArray.size()-1) = new Line(info);
}
void Screen::addMeter(PassInfo& info){
  meterArray.resize(meterArray.size()+1);
  meterArray.at(meterArray.size()-1) = new Meter(info);
}
void Screen::addRectangle(PassInfo& info){
  rectArray.resize(rectArray.size()+1);
  rectArray.at(rectArray.size()-1) = new Rectangle(info);
}

void Screen::draw(){
  lv_obj_set_style(lv_scr_act(), backGround);
  for(int y = 0; y < rectArray.size(); y++)
    rectArray.at(y)->draw();
  for(int y = 0; y < btnArray.size(); y++)
    btnArray.at(y)->draw(version);

  for(int y = 0; y <labelArray.size(); y++)
    labelArray.at(y)->draw();

  for(int y = 0; y < lineArray.size(); y++)
    lineArray.at(y)->draw();

  for(int y = 0; y < meterArray.size(); y++)
    meterArray.at(y)->draw();
}
void Screen::update(){
  for(int y = 0; y < btnArray.size(); y++)
    btnArray.at(y)->update(version);
  for(int y = 0; y < labelArray.size(); y++)
    labelArray.at(y)->update();

  for(int y = 0; y < meterArray.size(); y++)
    meterArray.at(y)->update();
}
void Screen::detect(){
  for(int y = 0; y < btnArray.size(); y++)
    btnArray.at(y)->checkState(version);
}
void Screen::remove(){
  for(int y = 0; y < btnArray.size(); y++)
    btnArray.at(y)->remove();

  for(int y = 0; y < labelArray.size(); y++)
    labelArray.at(y)->remove();

  for(int y = 0; y < lineArray.size(); y++)
    lineArray.at(y)->remove();

  for(int y = 0; y < meterArray.size(); y++)
    meterArray.at(y)->remove();

  for(int y = 0; y < rectArray.size(); y++)
    rectArray.at(y)->remove();
}
