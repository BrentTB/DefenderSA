#ifndef ASTEROID
#define ASTEROID

/**
 * @file Asteroid.h
 * @brief This file contains the information for construction an asteroid object. 
 * 
 */
#include "ProjectileEntity.h"

using namespace std;

/**
 * @brief Asteroid (stop sign) class which is a subclass of the ProjectileEntity class. 
 * The ProjectileEntity class is a subclass of the GameEntity class. 
 * 
 * This class manages all the specifics of the asteroids initialition. 
 */
class Asteroid : public ProjectileEntity
{
public:
    /**
     * @brief Construct a new Asteroid object. 
     * This sets up all the initial variables for the asteroid object. The size of the asteroids and their orientation is defined. 
     *  
     * @param x - This defines the asteroids x position for future movement of the object.
     * @param y - This defines the asteroids y position for future movement of the object.
     * @param direction - This is a boolean that sets the direction of the object with right as true and left as false. 
     */
    Asteroid(const double &x, const double &y, const bool &direction);

    /**
     * @brief Destroy the Asteroid object. 
     * This destroys the object and all of its entities.
     */
    ~Asteroid();
};

#endif