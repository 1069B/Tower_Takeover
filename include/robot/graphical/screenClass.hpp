#include "buttonClass.hpp"
#include "labelClass.hpp"
#include "meterClass.hpp"
#include "lineClass.hpp"
#include "rectangleClass.hpp"

#ifndef SCREENCLASS_H
#define SCREENCLASS_H

class Screen: protected AbstractGUI{
public:
  friend class Button;
  friend class Label;
  friend class Line;
  friend class Meter;
  friend class Rectangle;
  std::string& m_nextScreenID;
  std::vector<Button*> m_btnArray;
  std::vector<Label*> m_labelArray;
  std::vector<Meter*> m_meterArray;
  std::vector<Line*> m_lineArray;
  std::vector<Rectangle*> m_rectArray;
  lv_style_t* m_style;
  int& m_version;

  bool m_relation = false;
  std::string m_relatedScreen;
  bool m_inversed;
  std::function<bool()> m_relatedFunc;
  std::string m_pageID;

	Screen(const PassInfo& p_info);

  void addRelationship(const std::function<bool()> p_function, const bool p_inverse, const std::string p_otherScreen);
  std::string getRelatedScreen();
  std::function<bool()> getRelatedFunc();
  bool getInverse();
  bool isRelation();

	void addButton(const PassInfo& p_info);
	void addButtionAction(const PassInfo& p_info);

  void addLabel(PassInfo& p_info);

  void addLine(const PassInfo& p_info);

  void addMeter(const PassInfo& p_info);

  void addRectangle(const PassInfo& p_info);

  void draw();

  void changeBackground(lv_style_t& p_backColor);

  void update();

  void detect();

  void remove();
};
#endif // SCREENCLASS_H
