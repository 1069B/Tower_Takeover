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
  std::string& nextScreenID;
  std::vector<Button*> btnArray;
  std::vector<Label*> labelArray;
  std::vector<Meter*> meterArray;
  std::vector<Line*> lineArray;
  std::vector<Rectangle*> rectArray;
  lv_style_t* backGround;
  int& version;

  bool relation = false;
  std::string relatedScreen;
  bool inversed;
  std::function<bool()> relatedFunc;
  std::string pageID;

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
