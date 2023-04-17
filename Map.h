#ifndef CPPFIRST_MAP_H
#define CPPFIRST_MAP_H
#include "Robot.h"
#include "ostream"
using namespace std;

/** This class represents a map - it hold a matrix of integers that represent were a robot can and cannot be in
    0 - can 1 - cannot. it also hold a list of robots that locate in that map */

class Map
{
    int m_mapArray[7][7]{}; /// a nested array that represents the map
    int m_mapNumber; /// the number of the map
    Robot ** m_robotsInMap; /// dynamic array of pointer to robots
    int m_numOfRobots; /// number of robots in robotsInMap, starts at 0

public:
    /** default constructor - initialize the map with 0's
     */
    Map();

    /**
     * constructor
     * @param mapArray the nested array that represents the map
     * @param mapNumber the number of the map
     */
    Map(int mapArray[7][7], int mapNumber);

    /**
     * copyConstructor - creates a new map by using cMap - coping its parameters into map
     * @param cMap - a map we use to shallow copy to our map
     */
    Map(Map & cMap);

    /** destructor - deletes the map and free's its memory
     */
    ~Map();

    /**
     * adds a new robot to the map
     * @param robToAdd a pointer to robot to be added
     * @return true - if addition was successful, false - if a null pointer was received or some allocation failed
     */
    bool addRobot(Robot * robToAdd);

    /**
     * receives a robot serial number for a robot that is in the map and deletes it
     * @param robNumber a robot serial number that we want to delete from the map
     * @return true - if deletion was successful or robot is not in the map , false - if something went wrong (failed allocation)
     */
    bool deleteRobot(int robNumber);

    /**
     * searches for a robot in the map
     * @param robNumber a serial number for the robot we want to search
     * @return a pointer to the Robot if exists, nullptr otherwise
     */
    Robot * searchRobot(int robNumber)const;
    /**
     * receives a robot serial number and a move, if the robot exits in the map moves to robot to a new location according to the move
     * @param robNumber a serial number for a robot
     * @param move a char - options for the move - U - move Up, D - move Down, L - move Left, R - move Right
     */
    void moveRobot(int robNumber, char move) const;

    /**
     * adds two maps in bitwise or fashion, meaning if cells in the two map hold a 0 value in the new map that cell will be also 0
     * otherwise it will be 1.
     * after the adding will print the resulting map and the robots from the two maps that can be in that map
     * meaning their cube will be 0.
     * @param otherMap - the second map we operate on
     */
    void operator+(const Map &otherMap)const;

    /**
     * overrides the += operator for map - all the walls ('1') in the otherMap are added to the map
     * if in the new map a robot is not in a valid location - meaning in a cell with value 1, he will be deleted from the map
     * @param otherMap the otherMap we use for the += operator (right operand)
     * @return the new map resulting from the operation
     */
    const Map& operator+=(const Map &otherMap);

    /**
    * overrides the = operator for map - the map of the right map (in the operation) is copied to the left map
    * if in the new map a robot is not in a valid location - meaning in a cell with value 1, he will be deleted from the map
    * @param otherMap the otherMap we use for the = operator (right operand)
    * @return the new map resulting from the operation
    */
    Map& operator=(const Map &otherMap);

    /**
     *  overrides the == operator for map - checks if the maps are equal (not based on their robot!)
     * @param otherMap the map we compare to
     * @return true - if their equal. false - if not
     */
    bool operator==(const Map &otherMap)const;

    /**
     * overrides the << operator for map - prints the map and then prints the robots in the map
     * robots that is outside of the map will not be printed
     * @param out - ostream object - used to print the map
     * @param map - map to print
     */
    friend void operator<<(ostream &out, const Map &map);
    friend class Game;
};

#endif //CPPFIRST_MAP_H
