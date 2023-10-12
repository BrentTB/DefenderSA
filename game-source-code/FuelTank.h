#ifndef FUELTANK
#define FUELTANK

/**
 * @file FuelTank.h
 * @brief Initialisation of the fuelTank
 */
#include "GameEntity.h"

using namespace std;

/**
 * @class FuelTank
 * @brief Class that intitialises the FuelTank and is derived from the GameEntity class
 * 
 * @see GameEntity
 */
class FuelTank : public GameEntity
{
public:
    /**
     * @brief Construct a new Fuel Tank object
     * 
     * @param x - The x position of the entity
     * @param y  - The y position of the entity
     * @param direction - The direction of the entity
     */
    FuelTank(const double &x, const double &y, const bool &direction);

    /**
     * @brief Performs move, try fire, anything that needs to be done per frame. If it should fire, returns true
     * 
     * @param deltaTime - The change in time
     * @return true - If the entity should fire (FuelTank will never fire)
     * @return false - If the entity doesn't fire
     */
    bool update(const double &deltaTime) override;

    /**
     * @brief Destroy the Fuel Tank object
     */
    virtual ~FuelTank();

private:
    float fuelTimer_; /*shows the depletion of fuel*/
};

#endif
