#ifndef BOMBER
#define BOMBER

/**
 * @file Bomber.h
 * @brief Constructs the bomber object.
 */
#include "EnemyEntity.h"

using namespace std;

/**
 * @brief Bomber class
 * Manages the bomber object. Setting up initial variable size and functions. 
 * 
 */
class Bomber : public EnemyEntity
{
public:
    /**
     * @brief Construct a new Bomber object. 
     * 
     * @param x - The x position of the bomber
     * @param y - The y position of the bomber 
     * @param direction - a boolean indiating direction of the bomber 
     */
    Bomber(const double &x, const double &y, const bool &direction);

    /**
     * @brief Destroy the Bomber object
     * 
     */
    ~Bomber();

private:
    /**
     * @brief Function that controls the movement of the bomber object
     * The player's location can always be accessed through the static vector. 
     * 
     * @param deltaTime - this is a variable that keeps track of the time change.  
     */
    void move(const double &deltaTime) override;
    
    /**
     * @brief Checks if the bomber is at target, if it can then fire then true is returned.  
     * 
     * @param deltaTime - the change in time
     * @return true - if the bomber can fire
     * @return false - if the bomber can't fire
     */
    bool tryFire(const double &deltaTime) override;

    /**
     * @brief tuple variable to store target position
     */
    entityPosition target_;

    /**
     * @brief bool variable to store if object is at target
     */
    bool atTarget_;
};

#endif
