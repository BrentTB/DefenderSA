#ifndef PLAYERLASER
#define PLAYERLASER

/**
 * @file PlayerLaser.h
 * @brief The file that hold the playeLaser functionality
 */
#include "ProjectileEntity.h"

using namespace std;

/**
 * @class PlayerLaser
 * @brief The class holds the functionality for the PlayerLaser
 * The playerLaser is derived from the ProjectileEntity class which is derived from the GameEntity class
 * 
 * @see ProjectileEntity
 * @see GameEntity 
 */
class PlayerLaser : public ProjectileEntity
{
public:
    /**
     * @brief Construct a new Player Laser object
     * 
     * @param x - The playerLasers x position
     * @param y - The playerLasers y position 
     * @param direction - The direction the playerLaser is facing
     */
    PlayerLaser(const double &x, const double &y, const bool &direction); // set type to PlayerLaser and set speed

    /**
     * @brief Destroy the Player Laser object 
     */
    virtual ~PlayerLaser();
};

#endif
