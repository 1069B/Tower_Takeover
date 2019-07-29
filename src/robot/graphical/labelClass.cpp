#include "robot/graphical/labelClass.h"

Label::Label(PassInfo& info){// mode 0
  xOrgin = info.integer.at(0);
  yOrgin = info.integer.at(1);
  style1 = info.style1;
  format[0] = info.string1;
  mode = info.integer.at(2);
  switch(mode){
    case 0: break;
    case 1: intPointer = info.intPointer; break;
    case 2: intFunction = info.intFunction; break;
    case 3: doublePointer = info.doublePointer; break;
    case 4: doubleFunction = info.doubleFunction; break;
    case 5: boolPointer = info.boolPointer; break;
    case 6: boolFunction = info.boolFunction; break;
    case 7: stringPointer = info.stringPointer; break;
    case 8: stringFunction = info.stringFunction; break;
  }
}

void Label::setString(){
  std::string fmt = format[0];
  std::string sum = "";
  switch(mode){
    case 0:
      sum = fmt;
      break;
    case 1:
      sum = fmt.substr(0, fmt.find("%d")) + std::to_string(*intPointer) + fmt.substr(fmt.find("%d")+2);
      break;
    case 2:
      sum = fmt.substr(0, fmt.find("%d")) + std::to_string(intFunction()) + fmt.substr(fmt.find("%d")+2);
      break;
    case 3:
      sum = fmt.substr(0, fmt.find("%f")) + std::to_string(*doublePointer) + fmt.substr(fmt.find("%f")+2);
      break;
    case 4:
      sum = fmt.substr(0, fmt.find("%f")) + std::to_string(doubleFunction()) + fmt.substr(fmt.find("%f")+2);
      break;
    case 5:
      if(*boolPointer)
        sum = fmt.substr(0, fmt.find("%b")) + "True" + fmt.substr(fmt.find("%b")+2);
      else
        sum = fmt.substr(0, fmt.find("%b")) + "False" + fmt.substr(fmt.find("%b")+2);
      break;
    case 6:
      if(boolFunction())
        sum = fmt.substr(0, fmt.find("%b")) + "True" + fmt.substr(fmt.find("%b")+2);
      else
        sum = fmt.substr(0, fmt.find("%b")) + "False" + fmt.substr(fmt.find("%b")+2);
      break;
    case 7:
      sum = fmt.substr(0, fmt.find("%s")) + *stringPointer + fmt.substr(fmt.find("%s")+2);
      break;
    case 8:
      sum = fmt.substr(0, fmt.find("%s")) + stringFunction() + fmt.substr(fmt.find("%s")+2);
      break;
  }
  lv_label_set_text(obj1, sum.c_str());
}

void Label::draw(){
  obj1 = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(obj1, NULL, LV_ALIGN_IN_TOP_LEFT, xOrgin, yOrgin);
  setString();
  lv_obj_set_style(obj1, style1);
  state = true;
}
void Label::update(){
  if(state){
    setString();
  }
}
void Label::remove(){
  if(state){
    lv_obj_del(obj1);
    state = false;
  }
}
