#ifndef ENEMYENTITY
#define ENEMYENTITY

/**
 * @file EnemyEntity.h
 * @brief This file covers all the functions that are used for all enemy entities. 
 */
#include "GameEntity.h"

using namespace std;

/**
 * @class EnemyEntity Enemy Entity class
 * @brief This Enemy Entity class is the base class for all entities and is inhertied from GameEntity.  
 * 
 * @see GameEntity 
 */
class EnemyEntity : public GameEntity
{
public:
    /**
     * @brief Construct a new Enemy Entity object which is the parent class of all Enemies and is derived from the GameEnity class. 
     *  
     * @param x - This defines the EnemyEntity x position for future movement of the object.
     * @param y - This defines the EnemyEntity y position for future movement of the object.
     * @param direction - This is a boolean that sets the direction of the object with right as true and left as false. 
     */
    EnemyEntity(const double &x, const double &y, const bool &direction);

    /**
     * @brief This function updates the EnemyEntities my checking if the entity needs to move or fire through protected process. 
     * 
     * @param deltaTime - the change in time
     * @return true - if player can fire
     * @return false - if player cant fire
     */
    bool update(const double &deltaTime) override; // moves the sprite. Try fire (through private/protected functions)

    /**
     * @brief Destroy the Enemy Entity object
     * 
     */
    virtual ~EnemyEntity();

protected:
    /**
     * @brief This function is the function that gets overloaded by all the other move function for the enemies. 
     * 
     * @param deltaTime - The change in time
     */
    virtual void move(const double &deltaTime) = 0;    
    
    /**
     * @brief This checks the FireTimer, if the entity can fire, it returns true
     * 
     * @param deltaTime - The change in time
     * @return true - If the entity can fire
     * @return false - If the entity shouldn't fire yet
     */
    virtual bool tryFire(const double &deltaTime) = 0; 

    /**
     * @brief This function updates the x and y values based on the objects speed and angle. 
     * 
     * @param deltaTime - the change in time
     */
    void setPosition(const double &deltaTime); 
    
    /**
     * @brief Get the angle difference between the entity's angle and the angle to the target.
     * 
     * @param position tuple of the position and direction <x, y, direction> 
     * @return double - Angle difference 
     */
    double getAngleDifference(const entityPosition& position);
    
    /**
     * @brief This determines the distance from the target destination. 
     * 
     * @param x - This defines the EnemyEntity x position for future movement of the object.
     * @param y - This defines the EnemyEntity y position for future movement of the object.
     * @return double - The distance the entity is from the target
     */
    double distanceFromTarget(const double &x, const double &y);

    /**
     * @brief Stores how long its been since the object fired
     * 
     */
    float fireTimer_; 
};

#endif
