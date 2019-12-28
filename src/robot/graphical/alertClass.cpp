#include "robot/graphical/alertClass.hpp"

Alert::Alert(){
}

bool Alert::m_repeat = true;

int Alert::draw(const std::string p_message){
  m_obj1 = lv_mbox_create(lv_scr_act(), NULL);

  lv_mbox_set_text(m_obj1, p_message.c_str());
  static const char * btns[] ={"\221Resume Code", ""}; /*Button description. '\221' lv_btnm like control char*/
  lv_mbox_add_btns(m_obj1, btns, NULL);
  lv_obj_set_width(m_obj1, 350);
  lv_obj_align(m_obj1, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_mbox_set_action(m_obj1, alertResponse);
  m_repeat = true;
  while(m_repeat){
    pros::delay(5);
  }
  lv_mbox_start_auto_close(m_obj1, 0);
  return 0;
}

lv_res_t Alert::alertResponse(lv_obj_t * mbox, const char *txt){
  m_repeat = false;
  return LV_RES_OK;
}
