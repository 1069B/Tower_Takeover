#include "robot/graphical/meterClass.h"

Meter::Meter(PassInfo& info){
  xOrgin = info.integer.at(0);
  yOrgin = info.integer.at(1);
  rangeLow = info.integer.at(2);
  rangeHigh = info.integer.at(3);
  size = info.integer.at(4);
  angle = info.integer.at(5);
  numberOfDashes = info.integer.at(6);
  style1 = info.style1;// Default styles
  style2 = info.style2;
  intFunction = info.intFunction;
}

void Meter::draw(){
  state = true;
  obj1 = lv_lmeter_create(lv_scr_act(), NULL);
  lv_obj_set_style(obj1, style1);
  lv_lmeter_set_range(obj1, rangeLow, rangeHigh);
  lv_obj_set_size(obj1, size, size);
  lv_obj_align(obj1, NULL, LV_ALIGN_IN_TOP_LEFT, xOrgin, yOrgin);
  lv_lmeter_set_scale(obj1, angle, numberOfDashes);
  lv_lmeter_set_value(obj1, 42);

  obj2 = lv_label_create(obj1, NULL);
  lv_label_set_text(obj2, "42%");
  lv_obj_set_style(obj2, style2);
  lv_obj_align(obj2, NULL, LV_ALIGN_CENTER, 0, 0);
}

void Meter::update(){
  if(state){
    lv_lmeter_set_value(obj1, intFunction());
    lv_label_set_text(obj2, std::to_string(intFunction()).c_str());
  }
}

void Meter::remove(){
  if(state){
    lv_obj_clean(obj1);
    lv_obj_del(obj1);
    state = false;
  }
}
