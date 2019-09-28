#include "styles.h"
#include "abstractClass.h"

#ifndef BUTTONCLASS_H
#define BUTTONCLASS_H

class Button: protected AbstractGUI{
protected:
  friend class Screen;
  std::string& m_nextScreenVar;
  std::string m_linkedScreenID[6] = {"None","None","None","None","None","None"};// Corasponding screen
  int& m_varible;// Reference to what varible to change
  int m_value[6] = {0,0,0,0,0,0}; //Value set to above varible
  Timer m_timer;

  Button(PassInfo& p_info, std::string& p_nextScreenID);

  void defineAction(PassInfo& p_info);

  void checkState(int p_btnVer);

  bool returnState();

  void draw(int p_btnVer);
  void update(int p_btnVer);
  void remove();
};

#endif // BUTTONCLASS_H
