#ifndef GAME
#define GAME

/**
 * @file Game.h
 * @brief File that manages the running of the game
 * 
 */
#include <map>
#include <vector>
#include <memory>
#include "GameState.h"
#include "EntityList.h"
#include "GameEntity.h"
#include "EntityCreator.h"
#include "EntityManager.h"
#include "EntityDestroyer.h"
#include "WindowUI.h"
#include "HumanoidKidnapping.h"

using namespace std;
#define dpc dynamic_pointer_cast

/**
 * @class Game
 * @brief Runs the main game loop and operations of the game
 * 
 */
class Game
{
public:
    /**
     * @brief Construct a new Game object
     */
    Game();

    /**
     * @brief Begins the game for the first time
     */
    void startGame();
    
    /**
     * @brief Destroy the Game object
     */
    ~Game();

private:

    /**
     * @brief The main game loop that runs the game
     */
    void gameLoop();

    /**
     * @brief Resets all game variables to their initial values 
     */
    void resetGameVariables();

    /**
     * @brief Finds the state the game is in
     * @see GameState
     */
    void findState();

    /**
     * @brief Updates the position and all the properties of the entity
     */
    void updateEntites();
    
    /**
     * @brief If you level up the all entities are created 
     */
    void generateEntities();

    /**
     * @brief Stops displaying the entities that have been destroyed
     */
    void removeDestroyedEntities();    

    /**
     * @brief Finds the position of the screen that is in use.
     * Used to display the correct area of the screen, and to determine what entities are on and off screen
     */
    void findScreenPos();

    /**
     * @brief Renders the window that the game is played in. updates the window and displays the screen.
     */
    void renderScreen();

    shared_ptr<EntityManager> entityManager_; /*checks collisions and deletes entites*/ 
    EntityCreator entityCreator_;             /*creates new entites*/
    HumanoidKidnapping humanoidKidnapping_;   /*runs the capture of the humanoid*/  
    EntityDestroyer entityDestroyer_;         /*destroys entities*/  

    bool reset_;                /*reset boolean*/
    float deltaTime_;           /*change in time/time passed*/

    int score_;                 /*score of the player*/
    GameState state_;           /*enum from the GameState*/
    int level_;                 /*int holding the level*/
    int numEnemiesDestroyed_;   /*the number of enemies that have been destroyed, resets when level increases*/
    bool canPause_;             /*boolean showing if game is able to pause*/

    double screenPos_;          /*shows which postion of the screen is displayed*/
    double gameWidth_;          /*the width of the whole game*/
    WindowUI window_;           /*created the WindowUI function*/
};

#endif
