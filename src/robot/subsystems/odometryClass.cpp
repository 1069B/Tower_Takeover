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
  if(p_leftVelocity == p_rightVelocity){//No Turn
   //m_turnType = NOTURN;
   m_radiusLeft = 0;
   return m_radiusLeft;
 }
 else if(p_leftVelocity == 0){// Arc Turn
   //m_turnType = ARC;
   m_radiusLeft = 0;
   return m_radiusLeft;
 }
 else if(p_rightVelocity == 0){//Arc Turn
   //m_turnType = ARC;
   m_radiusLeft = -m_trakingDistanceTotal/(-1);
   return m_radiusLeft;
 }
 else if(p_leftVelocity/fabs(p_leftVelocity) != p_rightVelocity/fabs(p_rightVelocity)){//Opposed Turn
   //m_turnType = OPPOSED;
   m_radiusLeft = -m_trakingDistanceTotal/(p_rightVelocity/p_leftVelocity-1);
   return m_radiusLeft;
 }
 else{//Arc Turn
   //m_turnType = ARC;
   m_radiusLeft = -m_trakingDistanceTotal/(p_rightVelocity/p_leftVelocity-1);
   return m_radiusLeft;
 }
 return 404;
}

double Odometry::getRadiusRight(const double p_leftVelocity, const double p_rightVelocity){
  if(p_leftVelocity == p_rightVelocity){//No Turn
    //m_turnType = NOTURN;
    m_radiusRight = 0;
    return m_radiusRight;
  }
  else if(p_leftVelocity == 0){//Arc Turn
    //m_turnType = ARC;
    m_radiusRight = m_trakingDistanceTotal/(-1);
    return m_radiusRight;
  }
  else if(p_rightVelocity == 0){//Arc Turn
    //m_turnType = ARC;
    m_radiusRight = 0;
    return m_radiusRight;
  }
  else if(p_leftVelocity/fabs(p_leftVelocity) != p_rightVelocity/fabs(p_rightVelocity)){//Opposed Turning
    //m_turnType = OPPOSED;
    m_radiusRight = m_trakingDistanceTotal/(p_leftVelocity/p_rightVelocity-1);
    return m_radiusRight;
  }
  else{//Arc
    //m_turnType = ARC;
      m_radiusRight = m_trakingDistanceTotal/(p_leftVelocity/p_rightVelocity-1);
    return m_radiusRight;
  }
  return 404;
}

double Odometry::getOrientation(){
  m_orientation += getOrientationChange();
  return m_orientation;
}

double Odometry::getOrientationChange(){
  if(m_timer.preformAction()){
    m_velocityLeft = 100;//m_leftEncoder->getVelocity();
    m_velocityRight = 50;//m_rightEncoder->getVelocity();
    m_radiusAvg = ((getRadiusLeft(m_velocityLeft,m_velocityRight)+m_trackingDistanceLeft)+ (getRadiusRight(m_velocityLeft,m_velocityRight)-m_trackingDistanceRight))/2;
    m_radiusLeft = m_radiusAvg - m_trackingDistanceLeft;
    m_radiusRight = m_radiusAvg + m_trackingDistanceRight;
    m_velocityAvg = (m_velocityLeft+m_velocityRight)/2;

    m_currentOrientationTime = m_timer.getTime() / 1000;
    m_timeChange = m_currentOrientationTime - m_previousOrientationTime;
    m_previousOrientationTime = m_currentOrientationTime;

    if(fabs(m_radiusLeft) < 0.0001)
        m_radiusLeft = 0;
    if(fabs(m_radiusRight) < 0.0001)
        m_radiusRight = 0;

    if(m_velocityLeft == m_velocityRight){
      m_orientationChange = 0;
      m_radiusLeft = 0;
      m_radiusRight = 0;
      m_turnType = "Not Turning";
    }
    else if(m_radiusAvg == 0 || m_velocityAvg == 0){// Point and Extreme Opposed
      m_orientationChange = ((180)*(fabs(m_velocityLeft)+fabs(m_velocityRight))*(m_timeChange))/((M_PI)*(fabs(m_radiusLeft)+fabs(m_radiusRight)));
      m_orientationChange *= (m_velocityLeft/fabs(m_velocityLeft));
      m_turnType = "Extreme Opposed";
    }
    else if(m_velocityLeft == 0 || m_velocityRight == 0){//Extreme Arc Turn Right
      m_orientationChange = (m_velocityAvg*m_timeChange*360)/(2*M_PI*m_radiusAvg);
      m_turnType = "Extreme Arc";
    }
    else if(m_velocityLeft/fabs(m_velocityLeft) == m_velocityRight/fabs(m_velocityRight)){// Arc
      m_orientationChange = (m_velocityAvg*m_timeChange*360)/(2*M_PI*m_radiusAvg);
      m_turnType = "Arc";
    }
    else if(m_velocityLeft/fabs(m_velocityLeft) != m_velocityRight/fabs(m_velocityRight)){// Opposed
      m_orientationChange = (m_velocityAvg*m_timeChange*360)/(2*M_PI*m_radiusAvg);
      m_turnType = "Opposed";
    }
    else{
        m_orientationChange = 404;
        m_turnType = "Error";
    }
    m_timer.addActionDelay(100);
  }
  return m_orientationChange;
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

  l_gui.addLabel(m_name, 20, 50, whiteText, "Orientation: %f Deg", &m_orientationChange);
  //l_gui.addLabel(m_name, 20, 75, whiteText, "Orientation Velocity: %d", (std::function<int()>)std::bind(&Odometry::getOrientationVelocity, this));
  // l_gui.addLabel(m_name, 20, 100, whiteText, "Current XPosition: %d", &m_xPosition);
  // l_gui.addLabel(m_name, 20, 125, whiteText, "Velocity of XPosition: %d", (std::function<int()>)std::bind(&Odometry::getXVelocity, this));
  // l_gui.addLabel(m_name, 20, 150, whiteText, "Current YPosition: %d", &m_yPosition);
  // l_gui.addLabel(m_name, 20, 175, whiteText, "Velocity of YPosition: %d", (std::function<int()>)std::bind(&Odometry::getYVelocity, this));

  l_gui.addLabel(m_name, 20, 75, whiteText, "Left Velocity: %d", (std::function<int()>)std::bind(&Encoder::getVelocity, m_leftEncoder));
  l_gui.addLabel(m_name, 20, 100, whiteText, "Right Velocity: %d", (std::function<int()>)std::bind(&Encoder::getVelocity, m_rightEncoder));
  l_gui.addLabel(m_name, 20, 125, whiteText, "Left Radius: %f", &m_radiusLeft);
  l_gui.addLabel(m_name, 20, 150, whiteText, "Right Radius: %f", &m_radiusRight);
  l_gui.addLabel(m_name, 20, 175, whiteText, "Average Radius: %f", &m_radiusAvg);
  l_gui.addLabel(m_name, 20, 200, whiteText, "Time: %d", (std::function<int()>)std::bind(&Timer::lapTime, m_timer));

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
