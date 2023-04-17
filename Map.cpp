#include <iostream>
#include "Map.h"



Map::Map()
{
    m_mapNumber = 0;
    m_robotsInMap = nullptr;
    m_numOfRobots = 0;
    for(int i=0; i<7; i++)
    {
        for (int j = 0; j < 7; j++)
            m_mapArray[i][j] = 0;
    }
}

Map::Map(int mapArray[7][7], int mapNumber)
{
    m_mapNumber = mapNumber;
    m_robotsInMap = nullptr;
    m_numOfRobots = 0;
    for(int i=0; i<7; i++)
    {
        for (int j = 0; j < 7; j++)
            m_mapArray[i][j] = mapArray[i][j];
    }
}

Map::Map(Map & cMap)
{
    m_mapNumber = cMap.m_mapNumber;
    m_robotsInMap = new Robot * [cMap.m_numOfRobots];
    if(m_robotsInMap != nullptr)
    {
        for (int i=0; i < m_numOfRobots; i++)
            m_robotsInMap[i] = cMap.m_robotsInMap[i];
        m_numOfRobots = cMap.m_numOfRobots;
        for(int i=0; i<7; i++)
        {
            for (int j = 0; j < 7; j++)
                m_mapArray[i][j] = cMap.m_mapArray[i][j];
        }
    }
}

Map::~Map()
{
    for (int i = 0; i < m_numOfRobots; i++)
        delete m_robotsInMap[i];
    delete []m_robotsInMap;
}

bool Map::addRobot(Robot * robToAdd)
{
    if(robToAdd == nullptr)
        return false;
    Robot** temp;
    temp = new Robot * [m_numOfRobots + 1];
    if (!temp)
        return false;
    for (int i = 0; i < m_numOfRobots; i++)
        temp[i] = m_robotsInMap[i];
    temp[m_numOfRobots] = robToAdd;
    delete[]m_robotsInMap;
    m_robotsInMap = temp;
    m_numOfRobots++;
    return true;
}

Robot * Map::searchRobot(int robNumber)const
{
    for (int i = 0; i < m_numOfRobots; i++)
    {
        if (m_robotsInMap[i]->getSerialNum() == robNumber)
            return m_robotsInMap[i];
    }
    return nullptr;
}

bool Map::deleteRobot(int robNumber)
{
    Robot** temp;
    if(m_numOfRobots == 1)
    {
        delete m_robotsInMap[0];
        m_numOfRobots--;
        return true;
    }
    temp = new Robot * [m_numOfRobots - 1];
    if (!temp)
        return false;
    int j = 0;
    for (int i = 0; i < m_numOfRobots; i++)
    {
        if (m_robotsInMap[i]->getSerialNum() != robNumber)
        {
            temp[j] = m_robotsInMap[i];
            j++;
        }
        else
            delete m_robotsInMap[i];
    }
    delete[]m_robotsInMap;
    m_robotsInMap = temp;
    m_numOfRobots--;
    return true;
}

void Map::moveRobot(int robNumber, char move) const
{
    Robot * robToMove = searchRobot(robNumber);
    if(robToMove == nullptr)
        return;
    if (robToMove->getXLocation() == -1 && robToMove->getYLocation() == -1)
        return;
    int robXLoc = robToMove->getXLocation();
    int robYLoc = robToMove->getYLocation();
    if (move == 'U')
    {
        if (robYLoc == 6)
        {
            robToMove->setLocation(-1, -1);
            return;
        }
        if (m_mapArray[robXLoc][robYLoc + 1] == 0)
            robToMove->setLocation(robXLoc, ++robYLoc);
    }
    if (move == 'D')
    {
        if (robYLoc == 0)
        {
            robToMove->setLocation(-1, -1);
            return;
        }
        if (m_mapArray[robXLoc][robYLoc - 1] == 0)
            robToMove->setLocation(robXLoc, --robYLoc);
    }
    if (move == 'R')
    {
        if (robXLoc == 6)
        {
            robToMove->setLocation(-1, -1);
            return;
        }
        if (m_mapArray[robXLoc + 1][robYLoc] == 0)
            robToMove->setLocation(++robXLoc, robYLoc);
    }
    if (move == 'L')
    {
        if (robXLoc == 0)
        {
            robToMove->setLocation(-1, -1);
            return;
        }
        if (m_mapArray[robXLoc - 1][robYLoc] == 0)
            robToMove->setLocation(--robXLoc, robYLoc);
    }
    cout << "Robot: " << robNumber << " Map: " << m_mapNumber << " GPS: " << robXLoc << "," << robYLoc << endl;
}

void Map::operator+(const Map &map)const
{
    int resMap[7][7]; /// the resulting map
    for (int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(this->m_mapArray[i][j] == 0 && map.m_mapArray[i][j] == 0)
                resMap[i][j] = 0;
            else
                resMap[i][j] = 1;
        }
    }
    int robXLoc;
    int robYLoc;
    for (int j = 6; j > -1; j--) /// printing the resulting map
    {
        cout << "[";
        for (int i = 0; i < 6; i++)
        {
            cout << resMap[i][j] << " ";
        }
        cout << map.m_mapArray[6][j] << "]" << endl;
    }
    cout << endl;
    for (int i = 0; i < m_numOfRobots; i++) /// printing the robots that are valid from the first map
    {
        robXLoc = m_robotsInMap[i]->getXLocation();
        robYLoc = m_robotsInMap[i]->getYLocation();
        if (robXLoc != -1 && robYLoc != -1)
        {
            if(resMap[robXLoc][robYLoc] == 0)
                cout << "Robot: " << m_robotsInMap[i]->getSerialNum() << " GPS: " << robXLoc << "," << robYLoc << endl;
        }
    }
    for (int i = 0; i < map.m_numOfRobots; i++) /// now the second map
    {
        robXLoc = map.m_robotsInMap[i]->getXLocation();
        robYLoc = map.m_robotsInMap[i]->getYLocation();
        if (robXLoc != -1 && robYLoc != -1)
        {
            if(resMap[robXLoc][robYLoc] == 0)
                cout << "Robot: " << map.m_robotsInMap[i]->getSerialNum() << " GPS: " << robXLoc << "," << robYLoc << endl;
        }
    }
}

const Map& Map::operator+=(const Map &otherMap)
{
    for(int i = 0; i < 7; i++) /// changes the map
    {
        for (int j = 0; j < 7; j++)
        {
            if (otherMap.m_mapArray[i][j] == 1)
                m_mapArray[i][j] = 1;
        }
    }
    int robXLoc;
    int robYLoc;
    int i = 0;
    while (i < m_numOfRobots) /// deleting robots if needed
    {
        robXLoc = m_robotsInMap[i]->getXLocation();
        robYLoc = m_robotsInMap[i]->getYLocation();
        if (robXLoc != -1 && robYLoc != -1)
        {
            if(m_mapArray[robXLoc][robYLoc] == 1)
            {
                deleteRobot(m_robotsInMap[i]->getSerialNum());
                continue;
            }
        }
        i++;
    }
    return *this;
}

Map& Map::operator=(const Map &otherMap)
{
    if (this == &otherMap) /// self assigment
        return *this;
    for(int i = 0; i < 7; i++) /// changes the map
    {
        for (int j = 0; j < 7; j++)
                m_mapArray[i][j] = otherMap.m_mapArray[i][j];
    }
    int robXLoc;
    int robYLoc;
    int i = 0;
    while (i < m_numOfRobots) /// deleting robots if needed
    {
        robXLoc = m_robotsInMap[i]->getXLocation();
        robYLoc = m_robotsInMap[i]->getYLocation();
        if (robXLoc != -1 && robYLoc != -1)
        {
            if(m_mapArray[robXLoc][robYLoc] == 1)
            {
                deleteRobot(m_robotsInMap[i]->getSerialNum());
                continue;
            }
        }
        i++;
    }
    return *this;
}

bool Map::operator==(const Map &otherMap)const
{
    for(int i=0; i<7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (m_mapArray[i][j] != otherMap.m_mapArray[i][j])
                return false;
        }
    }
    return true;
}

void operator<<(ostream &out, const Map &map)
{
    for (int j = 6; j > -1; j--) /// printing the map
    {
        cout << "[";
        for (int i = 0; i < 6; i++)
        {
            cout << map.m_mapArray[i][j] << " ";
        }
        cout << map.m_mapArray[6][j] << "]" << endl;
    }
    cout << endl;
    for (int i = 0; i < map.m_numOfRobots; i++) /// prints the robots
    {
        int currRobotX = map.m_robotsInMap[i]->getXLocation();
        int currRobotY = map.m_robotsInMap[i]->getYLocation();
        int currRobotNum = map.m_robotsInMap[i]->getSerialNum();
        if (currRobotX != -1 && currRobotY != -1)
            cout << "Robot: " << currRobotNum << " Map: " << map.m_mapNumber << " GPS: " << currRobotX << "," << currRobotY << endl;
    }
}
