#include "robot/subsystems/odometryClass.hpp"
#include "robotClass.hpp"

Odometry::Odometry(Robot& p_robot, const std::string p_leftEncoder, const std::string p_rightEncoder, const std::string p_centerEncoder):
m_robot(p_robot){
  if(Encoder::findEncoder(p_leftEncoder) == NULL)
    m_leftEncoder = new Encoder(p_leftEncoder, 1, false);
  else
    m_leftEncoder = Encoder::findEncoder(p_leftEncoder);

  if(Encoder::findEncoder(p_rightEncoder) == NULL)
    m_rightEncoder = new Encoder(p_rightEncoder, 3, true);
  else
    m_rightEncoder = Encoder::findEncoder(p_rightEncoder);

  if(Encoder::findEncoder(p_centerEncoder) == NULL)
    m_centerEncoder = new Encoder(p_centerEncoder, 5, true);
  else
    m_centerEncoder = Encoder::findEncoder(p_centerEncoder);
}

double Odometry::getRadiusLeft(const double p_leftVelocity, const double p_rightVelocity){
  if(p_leftVelocity == p_rightVelocity){
    m_turnType = NOTURN;
    m_leftRadius = 0;
    return m_leftRadius;
  }
  else if(p_leftVelocity == 0){
    m_turnType = ARC;
    m_leftRadius = 0;
    return m_rightRadius;
  }
  else if(p_rightVelocity == 0){
    m_turnType = ARC;
    m_leftRadius = m_trakingDistanceLeft/(-1) * -1*(p_leftVelocity/fabs(p_leftVelocity));
    return m_rightRadius;
  }
  else if(p_leftVelocity/fabs(p_leftVelocity) != p_rightVelocity/fabs(p_rightVelocity)){
    m_turnType = OPPOSED;
    m_leftRadius = -m_trakingDistanceLeft/(p_rightVelocity/p_leftVelocity-1) * (p_leftVelocity/fabs(p_leftVelocity));
    return m_leftRadius;
  }
  else{
    m_turnType = ARC;
    m_leftRadius = -m_trakingDistanceLeft/(p_rightVelocity/p_leftVelocity-1) * (p_leftVelocity/fabs(p_leftVelocity));
    return m_leftRadius;
  }
  return 404;
}

double Odometry::getRadiusRight(const double p_leftVelocity, const double p_rightVelocity){
  if(p_leftVelocity == p_rightVelocity){
    m_turnType = NOTURN;
    m_rightRadius = 0;
    return m_rightRadius;
  }
  else if(p_leftVelocity == 0){
    m_turnType = ARC;
    m_rightRadius = m_trakingDistanceRight/(-1) * (p_rightVelocity/fabs(p_rightVelocity));
    return m_rightRadius;
  }
  else if(p_rightVelocity == 0){
    m_turnType = ARC;
    m_rightRadius = 0;
    return m_rightRadius;
  }
  else if(p_leftVelocity/fabs(p_leftVelocity) != p_rightVelocity/fabs(p_rightVelocity)){
    m_turnType = OPPOSED;
    m_rightRadius = m_trakingDistanceRight/(p_leftVelocity/p_rightVelocity-1) * (p_leftVelocity/fabs(p_leftVelocity));
    return m_rightRadius;
  }
  else{
    m_turnType = ARC;
    m_rightRadius = m_trakingDistanceRight/(p_leftVelocity/p_rightVelocity-1) * (p_leftVelocity/fabs(p_leftVelocity));
    return m_rightRadius;
  }
  return 404;
}

double Odometry::getOrientation(){
  m_orientation += getOrientationChange();
  return m_orientation;
}

double Odometry::getOrientationChange(){
  double l_orientationChange = 0;
  if(m_timer.preformAction()){
    double l_velocityRight = m_rightEncoder->getVelocity();
    double l_velocityLeft = m_leftEncoder->getVelocity();
    double l_radiusLeft = getRadiusLeft(l_velocityLeft, l_velocityRight);
    double l_radiusRight = getRadiusRight(l_velocityLeft, l_velocityRight);
    double l_radiusAverage = (l_radiusLeft + l_radiusRight)/2;

    m_currentOrientationTime = m_timer.getTime() / 1000;
    double l_timeChange = m_currentOrientationTime - m_previousOrientationTime;


    if(m_turnType == NOTURN){
      l_orientationChange = 0;
    }
    else{
      if((fabs(l_radiusLeft)-m_trakingDistanceLeft/2+fabs(l_radiusRight)-m_trakingDistanceRight/2)/2 == 0)// Point
        l_orientationChange = ((180)*(fabs(l_radiusLeft)+fabs(l_radiusRight))*(l_velocityLeft/fabs(l_velocityLeft))*(l_timeChange))/((M_PI)*(fabs(l_radiusLeft)+fabs(l_radiusRight)));

      else if((fabs(l_radiusLeft-m_trakingDistanceLeft)+ fabs(l_radiusRight-m_trakingDistanceRight))/2 != 0)// Non-Point
        l_orientationChange =  ((l_velocityLeft+l_velocityRight)*(l_timeChange)*180)/(M_PI*(l_radiusLeft + l_radiusRight));

      else
        l_orientationChange = 404;
    }

    m_previousOrientationTime = m_currentOrientationTime;
    m_timer.addActionDelay(10);
  }
  return l_orientationChange;
}

double Odometry::getOrientationVelocity(){
  m_currentOrientationVelocityTime = m_timer.getTime();
  m_currentOrientation = getOrientation();
  double l_timeChange = m_currentOrientationVelocityTime - m_previousOrientationVelocityTime;

  double l_angularVelocity = (m_currentOrientation - m_previousOrientation)/l_timeChange;
  return l_angularVelocity;
}

double Odometry::setOrientation(const double p_orientation){
  m_orientation = p_orientation;
  return 0;
}

double Odometry::getXposition(){
  return 0;
}

double Odometry::getXVelocity(){
  return 0;
}

double Odometry::setXposition(const double p_xPosition){
  m_xPosition = p_xPosition;
  return 0;
}

double Odometry::getYposistion(){
  return 0;
}

double Odometry::getYVelocity(){
  return 0;
}

double Odometry::setYposition(const double p_yPosition){
  m_yPosition = p_yPosition;
  return 0;
}

int Odometry::defineGUI(const std::string p_returnScreen){
  graphicalInterface& l_gui = m_robot.m_gui;
  m_leftEncoder->defineGUI(l_gui, "Odometry");
  m_centerEncoder->defineGUI(l_gui, "Odometry");
  m_rightEncoder->defineGUI(l_gui, "Odometry");

  l_gui.addScreen(m_name);
  l_gui.addLabel(m_name, 200, 10, redText, m_name);
  l_gui.addRectangle(m_name, 0, 0, 480, 40, whiteText);

  l_gui.addLabel(m_name, 20, 50, whiteText, "Orientation: %f Deg", (std::function<double()>)std::bind(&Odometry::getOrientation, this));
  //l_gui.addLabel(m_name, 20, 75, whiteText, "Orientation Velocity: %d", (std::function<int()>)std::bind(&Odometry::getOrientationVelocity, this));
  // l_gui.addLabel(m_name, 20, 100, whiteText, "Current XPosition: %d", &m_xPosition);
  // l_gui.addLabel(m_name, 20, 125, whiteText, "Velocity of XPosition: %d", (std::function<int()>)std::bind(&Odometry::getXVelocity, this));
  // l_gui.addLabel(m_name, 20, 150, whiteText, "Current YPosition: %d", &m_yPosition);
  // l_gui.addLabel(m_name, 20, 175, whiteText, "Velocity of YPosition: %d", (std::function<int()>)std::bind(&Odometry::getYVelocity, this));

  l_gui.addLabel(m_name, 20, 75, whiteText, "Left Velocity: %d", (std::function<int()>)std::bind(&Encoder::getVelocity, m_leftEncoder));
  l_gui.addLabel(m_name, 20, 100, whiteText, "Right Velocity: %d", (std::function<int()>)std::bind(&Encoder::getVelocity, m_rightEncoder));
  l_gui.addLabel(m_name, 20, 125, whiteText, "Left Radius: %f", &m_leftRadius);
  l_gui.addLabel(m_name, 20, 150, whiteText, "Right Radius: %f", &m_rightRadius);
  l_gui.addLabel(m_name, 20, 175, whiteText, "Average Radius: %f", &m_averageRadius);

  l_gui.addButton(m_name, 0, 300, 60, 140, 30);
  l_gui.addButtonAction(m_name, 0, m_leftEncoder->getName(), m_leftEncoder->getName());
  l_gui.addButton(m_name, 1, 300, 100, 140, 30);
  l_gui.addButtonAction(m_name, 1, m_centerEncoder->getName(), m_centerEncoder->getName());
  l_gui.addButton(m_name, 2, 300, 140, 140, 30);
  l_gui.addButtonAction(m_name, 2, m_rightEncoder->getName(), m_rightEncoder->getName());

  l_gui.addButton(m_name, 3, 160, 200, 150, 25);
  l_gui.addButtonAction(m_name, 3, "Go Back", p_returnScreen);
  return 0;
}
