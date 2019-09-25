#include "buttonClass.h"
#include "labelClass.h"
#include "meterClass.h"
#include "lineClass.h"
#include "rectangleClass.h"

#ifndef SCREENCLASS_H
#define SCREENCLASS_H

class Screen{
protected:
  friend class graphicalInterface;
  std::string& m_nextScreenID;
  std::vector<Button*> m_btnArray;
  std::vector<Label*> m_labelArray;
  std::vector<Meter*> m_meterArray;
  std::vector<Line*> m_lineArray;
  std::vector<Rectangle*> m_rectArray;
  lv_style_t* m_backGround;
  int& m_version;

  bool m_relation = false;
  std::string m_relatedScreen;
  bool m_inversed;
  std::function<bool()> m_relatedFunc;
  std::string m_pageID;

	Screen(PassInfo& p_info);

  void addRelationship(std::function<bool()> p_function, bool p_inverse, std::string p_otherScreen);
  std::string getRelatedScreen();
  std::function<bool()> getRelatedFunc();
  bool getInverse();
  bool isRelation();

	void addButton(PassInfo& p_info);
	void addButtionAction(PassInfo& p_info);

  void addLabel(PassInfo& p_info);

  void addLine(PassInfo& p_info);

  void addMeter(PassInfo& p_info);

  void addRectangle(PassInfo& p_info);

  void draw();

  void changeBackground(lv_style_t& p_backColor);

  void update();

  void detect();

  void remove();
};
#endif // SCREENCLASS_H
