#ifndef CPPFIRST_ROBOT_H
#define CPPFIRST_ROBOT_H

#include "ostream"
using namespace std;

/**
 * This class represents a robot - an object that holds a location - by x coordinate and y coordinate
 * the robot also has an id - serial number and a map number to whom he belongs
 */
class Robot
{
    int m_xCord; /// x coordinates of a robot
    int m_yCord; /// y coordinates of a robot
    int m_serialNum; /// serial number of a robot
    int m_mapNum; /// the map in which the robot exists
    static int numRobots; /// static parameter that represents the number of robots created so far
public:
    /**
     * constructor of a robot
     * @param xCord the x coordinates of the robot location
     * @param yCord the x coordinates of the robot location
     * @param mapNumber the mapNumber in which the robot will be set
     */
    Robot(int xCord, int yCord, int mapNumber);

    /**
     * copy constructor
     * @param cRob a Robot we copy its parameters to our robot
     */
    Robot(const Robot &cRob);

    /**
     * Destructor - deletes the robot
     */
    ~Robot();

    /**
     * sets a new location for the robot based on parameters received
     * @param xMove the new x coordinates location of the robot
     * @param yMove the new y coordinates location of the robot
     */
    void setLocation(int xMove, int yMove);

    /**
     * moves the robot to a new map
     * @param mapNumber to map to which the robot will be moved
     */
    void setMap(int mapNumber);

    /**
    * a getter for the x location of the robot
    * @return robot x coordinates
    */
    int getXLocation()const;

    /**
     * a getter for the y location of the robot
    * @return robot y coordinates
    */
    int getYLocation()const;

    /**
    * a getter for the serial number of the robot
    * @return robot serial number
    */
    int getSerialNum()const;

    /**
    * a getter for the y location of the robot
    * @return robot y coordinates
    */
    int getMapNum()const;

};


#endif //CPPFIRST_ROBOT_H
