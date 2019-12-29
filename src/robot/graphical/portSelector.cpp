#include "portSelector.hpp"
#include "robotClass.hpp"

PortSelector::PortSelector(Robot& p_robot, std::string p_name, std::string p_returnID, int& p_port):
m_robot(p_robot){
  m_name = p_name + "PortSelector";
  m_returnID = p_returnID;

  graphicalInterface& l_gui = m_robot.getGUI();

  l_gui.addScreen(m_name, 20, 20, 440, 200);// Add Default
  int l_id = 1;
  for(int y = 20; y<4;y+= 40){
    for(int x = 20; x < 5; x+=40){
      l_gui.addButton(m_name, l_id, x, y, 30, 30, p_port);
      l_gui.addButtonAction(m_name, l_id, std::to_string(l_id), p_returnID, 0, l_id);
      l_id++;
    }
  }






}
