#ifndef CPPFIRST_GAME_H
#define CPPFIRST_GAME_H
#include "Map.h"


/** This class represents a Game involving maps and robots.
 * the game holds two default maps where we play the game, the menu functions is where the game is played
 * a menu is printed and the player have options on how to play the game
 */
class Game
{
    Map * m_map1;
    Map * m_map2;

    /**
     * helper function for the first case in the menu - adds a robot to the game
     * @return  false if something failed during the addition - like memory allocation will clean the game if so
     * true if nothing malfunctioned during the adding process
     */
    bool addRobotToGame();

    /**
     * helper function for the second case in the menu - deletes a robot from the game
     * @return  false if something failed during the deletion, true otherwise.
     */
    bool deleteRobotFromGame();

    /**
    * helper function for the third case in the menu - moves a robot in a map by user input
    */
    void moveRobotInGame();

public:
    /**
     * constructor - initializes the maps
     */
    Game();

    /** destructor - default
     */
    ~Game();

    /**
     * copy constructor - creates the game using the maps of the cGame
     * @param cGame - a game to create our game from
     */
    Game(const Game &cGame);

    /** the main method of the game - starts a game according to the instructions - opens a menu for the user to
     * play the game.
     * @return  false if something went wrong during the run, true otherwise.
     */
    bool play();

};

#endif //CPPFIRST_GAME_H
