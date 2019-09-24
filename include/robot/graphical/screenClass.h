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

	Screen(PassInfo& info);

  void addRelationship(std::function<bool()> func, bool inverse, std::string otherScreen);
  std::string getRelatedScreen();
  std::function<bool()> getRelatedFunc();
  bool getInverse();
  bool isRelation();

	void addButton(PassInfo& info);
	void addButtionAction(PassInfo& info);

  void addLabel(PassInfo& info);

  void addLine(PassInfo& info);

  void addMeter(PassInfo& info);

  void addRectangle(PassInfo& info);

  void draw();

  void changeBackground(lv_style_t& backColor);

  void update();

  void detect();

  void remove();
};
#endif // SCREENCLASS_H
