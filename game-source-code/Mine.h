#ifndef MINE
#define MINE

/**
 * @file Mine.h
 * @brief The file that holds the mine object construction 
 */
#include "ProjectileEntity.h"

using namespace std;

/**
 * @class Mine
 * @brief Thic class creates the mine object. 
 * It is derived from the ProjectileEntity class which is derived from the GameEntity class.
 * @see ProjectileEntity 
 */
class Mine : public ProjectileEntity
{
public:
    /**
     * @brief Construct a new Mine object
     * This sets the entity type to Mine
     * @param x - The x position of the Mine 
     * @param y - The y position of the Mine
     * @param direction - The direction the mine faces (doesn't matter)
     */
    Mine(const double &x, const double &y, const bool &direction); 

    /**
     * @brief Destroy the Mine object
     */
    virtual ~Mine();
};
#endif
