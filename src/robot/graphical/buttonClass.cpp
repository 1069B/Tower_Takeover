#include "robot/graphical/buttonClass.h"

Button::Button(PassInfo& info, std::string& nextScreenID):timer(false), varible(*info.intPointer), nextScreenVar(nextScreenID){
  id = info.integer.at(0); // Id for the Button
  xOrgin = info.integer.at(1); //Every thing is in realtion to the upper left coner
  yOrgin = info.integer.at(2);
  length = info.integer.at(3);
  width = info.integer.at(4);
  style1 = info.style1;
  style2 = info.style2;
}

void Button::defineAction(PassInfo& info){
  mode = info.integer.at(3);
  linkedScreenID[info.integer.at(1)] = info.string2;// Corasponding screen
  value[info.integer.at(1)] = info.integer.at(2); //Value set to above varible
  format[info.integer.at(1)] = info.string1;
}

void Button::draw(int btnVer) {
  obj1 = lv_btn_create(lv_scr_act(), NULL);
  obj2 = lv_label_create(obj1, NULL);
  lv_obj_align(obj1, NULL, LV_ALIGN_IN_TOP_LEFT, xOrgin, yOrgin);
  lv_obj_set_free_num(obj1, id);   /*Set a unique number for the button*/
  lv_obj_set_size(obj1, length, width); //set the button size
  lv_btn_set_style(obj1, LV_BTN_STYLE_REL, style1); //set the relesed style
  lv_btn_set_style(obj1, LV_BTN_STYLE_PR, style2); //set the pressed style
  lv_label_set_text(obj2, format[btnVer].c_str());
   state = true;
}

void Button::update(int btnVer){
  lv_label_set_text(obj2, format[btnVer].c_str());
}

void Button::remove() {
  if(state){
    lv_obj_clean(obj1);
    lv_obj_del(obj1);
    state = false;
  }
}

void Button::checkState(int btnVer){
  if(state && timer.preformAction()){
    lv_btn_state_t buttonState = lv_btn_get_state(obj1);
    if(buttonState == LV_BTN_STATE_PR){
      nextScreenVar = linkedScreenID[btnVer];
      if(mode == 0)
        varible = value[btnVer];
      else if(mode == 1)
        varible += value[btnVer];

      timer.addActionDelay(500);
      return;
    }
  }
}

bool Button::returnState(){
  if(state && timer.preformAction()){
    lv_btn_state_t buttonState = lv_btn_get_state(obj1);
    if(buttonState == LV_BTN_STATE_PR){
      timer.addActionDelay(500);
      return true;
    }
  }
  return false;
}
