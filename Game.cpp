#include "Game.h"
#include "iostream"
using namespace std;

int mapArray1 [7][7] = {{1,1,1,0,0,1,1},{0,0,0,0,1,1,0}
        ,{0,1,1,0,0,0,0},{0,0,1,1,1,0,1}
        ,{0,0,0,1,1,0,1},{0,1,1,1,1,0,0},
                 {0,0,0,0,0,1,1}};
int mapArray2 [7][7] = {{1,1,0,0,1,1,1},{0,1,0, 1,1,1,1}
        ,{1,0,0,1,0,0,0},{0,1,0,1,0,1,0},
                 {0,1,0,0,0,1,0},{0,1,1,1,1,1,1},{0,0,1,1,1,1,1}};


Map *map1 = new Map(mapArray1, 1);
Map *map2= new Map(mapArray2, 2);

Game::Game()
{
    m_map1 = map1;
    m_map2 = map2;
    m_map1->m_mapNumber = 1;
    m_map2->m_mapNumber = 2;
}

Game::~Game()
{
    delete map1;
    delete map2;
}

Game::Game(const Game &cGame)
{
    m_map1 = cGame.m_map1;
    m_map2 = cGame.m_map2;
}

bool Game::addRobotToGame()
{
    int mapNumber;
    int xCord;
    int yCord;
    cout << "Enter MAP number: " << endl;
    cin >> mapNumber;
    cout << "Enter Coordinates (X,Y): " << endl;
    cin >> xCord >> yCord;
    if (xCord > 6 || xCord < 0 || yCord > 6 || yCord < 0)
    {
        cout << "Invalid location" << endl;
        return true; /// not really true but nothing malfunctioned so we dont want to clean the game
    }
    if(mapNumber == 1 && m_map1->m_mapArray[xCord][yCord] == 1 || mapNumber == 2 && m_map2->m_mapArray[xCord][yCord] == 1)
    {
        cout << "Invalid location" << endl;
        return true;
    }
    Robot * rob = new Robot(xCord, yCord, mapNumber);
    /// adding to robot to the map
    if (mapNumber == 1)
    {
        if (!m_map1->addRobot(rob))
            return false;
    }
    if(mapNumber == 2)
    {
        if (!m_map2->addRobot(rob))
            return false;
    }
    cout << "New Robot: " << rob->getSerialNum() << " MAP: " << mapNumber << " GPS: " << xCord << "," << yCord << endl;
    return true;
}

bool Game::deleteRobotFromGame()
{
    int robotNumber;
    cout << "Enter Robot number: " << endl;
    cin >> robotNumber;
    /// deleting the robot from the maps - will first search the robots in both map - if exists deletes it, if not do nothing
    Robot * robToDel;
    /// well save the robot parameters before deleting for printing
    int robMapNum;
    int robXLoc;
    int robYLoc;
    robToDel = m_map1->searchRobot(robotNumber);
    if(robToDel != nullptr)
    {
        robMapNum = 1;
        robXLoc = robToDel->getXLocation();
        robYLoc = robToDel->getYLocation();
        if (!m_map1->deleteRobot(robotNumber)) /// checks that deletion hasn't failed
            return false;
    }
    else /// robot is in the second map
    {
        robToDel = m_map2->searchRobot(robotNumber);
        if(robToDel == nullptr)
            return false;
        robMapNum = 2;
        robXLoc = robToDel->getXLocation();
        robYLoc = robToDel->getYLocation();
        if (!m_map2->deleteRobot(robotNumber))
            return false;
    }
    cout << "Robot deleted : " << robotNumber << " MAP: " << robMapNum << " GPS: " << robXLoc << "," << robYLoc << endl;
    return true;
}

void Game::moveRobotInGame()
{
    int robotNum;
    char direction;
    cout << "Enter Robot number: " << endl;
    cin >> robotNum;
    cout << "Enter Direction: " << endl;
    cin >> direction;
    Robot *robToMove = m_map1->searchRobot(robotNum);
    if (robToMove != nullptr)
        m_map1->moveRobot(robotNum, direction);
    else /// robot is in map 2 (not in map 1)
        m_map2->moveRobot(robotNum, direction);
}

bool Game::play()
{
    string input;
    int inputNum;
    while (true)
    {
        cout << "Robot Control Menu " << endl;
        cout << "1. Add Robot " << endl;
        cout << "2. Delete Robot " << endl;
        cout << "3. Move Robot " << endl;
        cout << "4. Operator + " << endl;
        cout << "5. Operator += " << endl;
        cout << "6. Operator = " << endl;
        cout << "7. Operator == " << endl;
        cout << "8. Operator << " << endl;
        cout << "9. Quit" << endl;
        cout << "Input your option: " << endl;
        cin >> input;
        if(input.length() > 1 || !isdigit(input[0]))
        {
            cout << "Invalid input" << endl;
            continue;
        }
        inputNum = stoi(input);
        switch (inputNum)
        {
            case 1: /// Add Robot
                if(!addRobotToGame())
                {
                    return false;
                }
                continue;
            case 2: /// Delete Robot
                if(!deleteRobotFromGame())
                {
                    return false;
                }
                continue;
            case 3: /// Move Robot
                moveRobotInGame();
                continue;
            case 4: /// Operator +
                *m_map1+*m_map2;
                continue;
            case 5: /// Operator +=
                int mapToAssign;
                cout << "Override MAP number: " << endl;
                cin >> mapToAssign;
                if(mapToAssign == 1)
                    *m_map1+=*m_map2;
                else if (mapToAssign == 2)
                    *m_map2+=*m_map1;
                else
                    cout << "Invalid MAP number" << endl;
                continue;
            case 6: /// operator =
                int mapToAssign2;
                cout << "Override MAP number: " << endl;
                cin >> mapToAssign2;
                if (mapToAssign2 == 1)
                    *m_map1=*m_map2;
                else if (mapToAssign2 == 2)
                    *m_map2=*m_map1;
                else
                    cout << "Invalid MAP number" << endl;
                continue;
            case 7: /// operator ==
                if(*m_map1 == *m_map2)
                    cout << "TRUE" << endl;
                else
                    cout << "FALSE" << endl;
                continue;
            case 8: /// operator <<
                int mapNumber;
                cout << "Please enter MAP number: " << endl;
                cin >> mapNumber;
                if (mapNumber == 1)
                    cout << *m_map1;
                else if (mapNumber == 2)
                    cout << *m_map2;
                else
                    cout << "Invalid MAP number" << endl;
                continue;
            case 9: /// bye
                return true;
            default:
                cout << "Invalid input" << endl;
                continue;
        }
    }
}