#include <iostream>
#include "Robot.h"

int Robot::numRobots = 0;

Robot::Robot(int xCord, int yCord, int mapNumber)
{
    numRobots ++;
    m_xCord = xCord;
    m_yCord = yCord;
    m_mapNum = mapNumber;
    m_serialNum = numRobots;
}

Robot::Robot(const Robot &cRob)
{
    m_xCord = cRob.m_xCord;
    m_yCord = cRob.m_yCord;
    m_serialNum = cRob.m_serialNum;
    m_mapNum = cRob.m_mapNum;
}

Robot::~Robot()
= default;

void Robot::setLocation(int xMove, int yMove)
{
    m_xCord = xMove;
    m_yCord = yMove;
}

void Robot::setMap(int mapNumber)
{
    m_mapNum = mapNumber;
}

int Robot::getXLocation()const
{
    return this->m_xCord;
}

int Robot::getYLocation() const
{
    return this->m_yCord;
}

int Robot::getSerialNum()const
{
    return this->m_serialNum;
}

int Robot::getMapNum()const
{
    return this->m_mapNum;
}