#ifndef LANDERLASER
#define LANDERLASER

/**
 * @file LanderLaser.h
 * @brief File that stores the LanderLaser definition
 */
#include "ProjectileEntity.h"

using namespace std;

/**
 * @class LanderLaser
 * @brief The class that constructs the LanderLaser entity
 */
class LanderLaser : public ProjectileEntity
{
public:
    /**
     * @brief Construct a new Lander Laser object
     * Sets the entity type to LanderLaser 
     * @param x - The x position of the Laser 
     * @param y - The y position of the Laser
     * @param direction - The direction of the laser 
     */
    LanderLaser(const double &x, const double &y, const bool &direction); 

    /**
     * @brief Destroy the Lander Laser object
     */
    virtual ~LanderLaser();
};

#endif
