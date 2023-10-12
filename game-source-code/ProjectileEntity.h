#ifndef PROJECTILEENTITY
#define PROJECTILEENTITY

/**
 * @file ProjectileEntity.h
 * @brief The file holds the definition of the Projectile Entity class
 */
#include "GameEntity.h"

using namespace std;

/**
 * @class ProjectileEntity
 * @brief This class manages the functionality of the Projectiles 
 * This class is derived from GameEntity. 
 * 
 * @see GameEntity
 */
class ProjectileEntity : public GameEntity
{
public:
    /**
     * @brief Construct a new Projectile Entity object
     * 
     * @param x - The projectile entity x position
     * @param y - The projectile entity y position
     * @param direction - The direction the projectile is facing
     */
    ProjectileEntity(const double &x, const double &y, const bool &direction);

    /**
     * @brief This updates all the private function of the projectileEntity 
     * 
     * @param deltaTime - The change in time
     * @return true - Will never return true because a projectile can't fire a projectile
     * @return false - projectiles cant fire
     */
    bool update(const double &deltaTime) override; 

    /**
     * @brief Get the Tilt Angle of the object
     * This allows projectiles to go to the players exact angle
     * 
     * @return double - The tilt angle  
     */
    double getTiltAngle() override;

    /**
     * @brief Destroy the Projectile Entity object
     */
    virtual ~ProjectileEntity();

protected:
    /**
     * @brief Moves the sprite,
     * The player's location can be accessed through the static vector
     * 
     * @param deltaTime - The change in position
     */
    void move(const double &deltaTime); 
};

#endif