#include "robot/graphical/rectangleClass.h"

Rectangle::Rectangle(PassInfo& info){
  xOrgin = info.integer.at(0); //Every thing is in realtion to the upper left coner
  yOrgin = info.integer.at(1);
  length = info.integer.at(2);
  width = info.integer.at(3);
  mode = info.integer.at(4);
  if(mode)
    lv_styleFunction = info.lv_styleFunction;
  else
    style1 = info.style1;
}

void Rectangle::draw(){
  obj1 = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(obj1, length, width);
  lv_obj_set_style(obj1, style1);
  lv_obj_align(obj1, NULL, LV_ALIGN_IN_TOP_LEFT, xOrgin, yOrgin);
  state = true;
}

void Rectangle::update(){
  if(state && mode){
    style1 = lv_styleFunction();
    lv_obj_set_style(obj1, style1);
  }
}

void Rectangle::remove(){
  if(state){
    lv_obj_del(obj1);
    state = false;
  }
}
