#include "styles.hpp"
#include "abstractClass.hpp"

#ifndef BUTTONCLASS_H
#define BUTTONCLASS_H

class Button: protected AbstractGUI{
public:
  //friend class Screen;
  std::string& m_nextScreenVar;
  std::string m_linkedScreenID[6] = {"None","None","None","None","None","None"};// Corasponding screen
  int& m_varible;// Reference to what varible to change
  int m_value[6] = {0,0,0,0,0,0}; //Value set to above varible
  Timer m_timer;

  Button(const PassInfo& p_info, std::string& p_nextScreenID);

  void defineAction(const PassInfo& p_info);

  void checkState(const int p_btnVer);

  bool returnState();

  void draw(const int p_btnVer);
  void update(const int p_btnVer);
  void remove();
};

#endif // BUTTONCLASS_H
