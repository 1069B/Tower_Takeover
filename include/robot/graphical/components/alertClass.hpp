#include "abstractClass.hpp"

#ifndef ALERTCLASS_H
#define ALERTCLASS_H

class Alert: protected AbstractGUI{
public:
  static bool m_repeat;

  Alert();

  int draw(const std::string p_message);

  static lv_res_t alertResponse(lv_obj_t * btnm, const char *txt);
};

extern Alert g_alert;

#endif // ALERTCLASS_H
