#ifndef GAMEENTITY
#define GAMEENTITY

/**
 * @file GameEntity.h
 * @brief File that mangages all the game entitiy functions
 */
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <utility>
#include <memory>
#include "EntityList.h"
#include "Clock.h"

using namespace std;
using entityPosition = tuple<double, double, bool>;
using entitySize = tuple<double, double>;

/**
 * @class GameEntity
 * @brief This is the parent game entity class. All game entities are derived from this class. 
 */
class GameEntity
{
public:
    /**
     * @brief Construct a new Game Entity object
     * 
     * @param x - The x position of the entity
     * @param y - The y position of the entity
     * @param direction - The direction the entity faces
     */
    GameEntity(const double &x, const double &y, const bool &direction);

    /**
     * @brief Get the Position object 
     * 
     * @return entityPosition (x, y)
     */
    entityPosition getPosition();

    /**
     * @brief Get the Size object
     * 
     * @return entitySize (width, height)
     */
    entitySize getSize();

    /**
     * @brief Get the Type object
     * 
     * @return EntityList 
     */
    EntityList getType();          

    /**
     * @brief Get the Defeat Score object
     * 
     * @return int - the score if you defeat one of these enemies
     */
    int getDefeatScore();

    /**
     * @brief Performs move, try fire, anything that needs to be done per frame. If it should fire, returns true
     * 
     * @param deltaTime - The change in time
     * @return true - If the entity should fire
     * @return false - The entity doesnt fire
     */
    virtual bool update(const double &deltaTime) = 0; 

    /**
     * @brief This sets isDestroyed_ to true
     * 
     */
    void destroy();

    /**
     * @brief Checks whether an entity is destroyed 
     * 
     * @return true - If it is destoyed 
     * @return false - Is not destroyed 
     */
    bool isDestroyed();

    /**
     * @brief Get the Tilt Angle object
     * 
     * @return double - returns 0 for objects that shouldnt tilt, and angle_ for objects that should
     */
    virtual double getTiltAngle(); 

    /**
     * @brief Allows the screen to wrap around when it gets tot hen end of gameWidth
     * 
     * @param centreX - Position of the centre x-pos
     * @param gameWidth - The width of the whole game
     */
    void wrapPosition(const double& centreX, const double& gameWidth);

    /**
     * @brief Shared ptr of all objects existing in the game.
     * Object 0 is the player
     */
    static vector<shared_ptr<GameEntity>> allEntities; 
    
    /**
     * @brief Destroy the Game Entity object
     */
    virtual ~GameEntity();

protected:
    double x_;          /*The x-position*/
    double y_;          /*The y-position*/
    double direction_;  /*The direction of the entity*/
    double speed_;      /*The speed of the entity*/
    double angle_;      /*The angle of the entity if needed*/
    double width_;      /*The width of the entity*/
    double height_;     /*The height of the entity*/
    int defeatScore_;   /*The score given for defeating this entity*/

    int topBorder_;     /*The size of the top border*/
    int bottomBorder_;  /*The size of the bottom border*/

    EntityList type_;   /*The enum type of entity*/
    bool isDestroyed_;  /*bool returned if the entity is destroyed or not*/
};

#endif