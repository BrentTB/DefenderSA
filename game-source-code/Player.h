#ifndef PLAYER
#define PLAYER

/**
 * @file Player.h
 * @brief File that holds all the Player class
 */
#include "GameEntity.h"
#include "UserInput.h"

using namespace std;

/**
 * @class Player
 * @brief This is the player class, it manages all the functions associated with player
 * This class is a derived class from GameEntity
 * 
 * @see GameEntity 
 */
class Player : public GameEntity
{
public:
    /**
     * @brief Construct a new Player object
     * 
     * @param x - The players x position
     * @param y - The players y position 
     * @param direction - The direction the player is facing 
     */
    Player(const double &x, const double &y, const bool &direction);

    /**
     * @brief Set the User Input object (userInput_)
     * This is used to move the player. 
     * 
     * @param userInput This is a map that takes in the UserInput and a bool of if it is pressed or not. 
     */
    void setUserInput(const map<UserInput, bool> &userInput); // sets userInput_, which is used to move the player

    /**
     * @brief This function updates all the players functions. 
     * 
     * @param deltaTime - The change in time 
     * @return true - If player can fire
     * @return false - If player cannot fire
     */
    bool update(const double &deltaTime) override;

    /**
     * @brief This shows that the player is saving a humanoid from a Lander
     * 
     * @param isSaving 
     */
    void isSaving(const bool& isSaving);

    /**
     * @brief Sets a bool to see if the player is saving or not
     * 
     * @return true - is saving
     * @return false - is not saving
     */
    bool isSaving();

    /**
     * @brief Refills the fuel of the player when the player collides with a fuelTank object. 
     * 
     */
    void refillFuel();

    /**
     * @brief This sets if the shield is on by changing the type of the object from Player to PlayerShield.
     * If the shieldTimer is < the time limit, it does nothing
     * @param shieldOn - if the shield is on
     */
    void changeShield(const bool &shieldOn); 

    /**
     * @brief Levels the player up by resetting the player's shieldCount
     * 
     */
    void levelUp();

    /**
     * @brief Get the Player Information object
     * 
     * @return tuple<int,double> Returns the shieldCound and the fuelLevel
     */
    tuple<int,double> getPlayerInformation(); 

    /**
     * @brief Destroy the Player object
     */
    virtual ~Player();

private:
    /**
     * @brief This moves the sprite, 
     * The players location can always be accessed through the static vector
     * 
     * @param deltaTime - The change in time
     */
    void move(const double &deltaTime); 
    
    /**
     * @brief This checks the FireTimer, if it can fire then it calls the enitiyCreator to create a projectile entity. 
     * 
     * @param deltaTime - The change in time
     * @return true - Can fire
     * @return false - Cannot fire
     */
    bool tryFire(const double &deltaTime); 
    
    /**
     * @brief Set the Shield object
     * 
     * @param shieldOn - Bool if shield is on or off
     */
    void setShield(const bool &shieldOn);

    /**
     * @brief PLayer falls out the sky when it runs out of fuel
     * 
     * @param deltaTime - the change is time
     */
    void fall(const double &deltaTime);

    int shieldCount_;   /*Stores how many shields the player has left*/
    float shieldTimer_;              /*stores how long its been since the shield started*/
    double fuel_;       /*Stores how much fuel the player has left*/

    map<UserInput, bool> userInput_; /*The map for the keys inputted*/
    float fireTimer_;                /*stores how long its been since the object fired*/
    float fireDelay_;                /*stores the delay between firing*/     
    bool isSaving_;                  /*shows whether the player is saving a humanoid or not*/
};

#endif
