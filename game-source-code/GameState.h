#ifndef GAMESTATE
#define GAMESTATE

/**
 * @file GameState.h
 * @brief File that holds the gamestate enum
 * 
*/

/**
 * @class GameState
 * @brief enum holding all the GameStates the game could be in
 * Where the game is, if we are at the start screen, playing, paused, or if we have lost
 */
enum class GameState
{
    /**
     * @enum This enum holds the possible Game States 
     * 
     */
    Start = 0,  /*The begining of the game*/
    Playing,    /*The game is currently being played*/ 
    Pause,      /*The game is paused*/
    Info,       /*The information screne is shown*/
    GameOver,   /*The game is over and the player lost*/
    Exit        /*The escape key is pressed and the game closes*/
};

#endif