#ifndef ENTITYMANAGER
#define ENTITYMANAGER

/**
 * @file EntityManager.h
 * @brief File that controls the management of entities and their positions
 */
#include "GameEntity.h"

using namespace std;
/**
 * @class EntityManager
 * @brief The class that manages all the entities used in the game  
 * 
 */
class EntityManager
{
public:
    /**
     * @brief Construct a new Entity Manager object
     * 
     * @param topBorderHeight - Top boarder height of the screen
     * @param bottomBorderHeight - Bottom border height of the screen
     * @param screenWidth - The width of the screen that is visible
     */
    EntityManager(const double &topBorderHeight, const double &bottomBorderHeight, const double &screenWidth);

    /**
     * @brief Function that checks whether an entity is on screen 
     * 
     * @param x - Entity x-position
     * @param y - Entity y-position
     * @param screenPos - Position of the visible screen
     * @return true - If entity is on the screen
     * @return false - if entity is not on the screen
     */
    bool onScreen(const double &x, const double &y, const double &screenPos);

    /**
     * @brief Checks if the two entities collide
     * For a shielded player: the ship dies when it hits the shielded player, but the shielded player doesnt die
     * @param entity1 - Entity 1 to check overlap
     * @param entity2  - Entity 2 to check with overlap
     * @return true - If hitboxes do overlap
     * @return false - If hitboxes don't overlap
     */
    bool hitboxOverlap(const shared_ptr<GameEntity> &entity1, const shared_ptr<GameEntity> &entity2); 

    /**
     * @brief This function deletes all projectiles if they're off screen, except mines
     * 
     * @param screenPos - Position the visible screen is at  
     */
    void checkOffScreenProjectiles(const double &screenPos); 

    /**
     * @brief This function checks if any entities collided. 
     */
    void checkEntityCollisions();

    /**
     * @brief Function that checks if the player is colliding with the fuelTank object 
     * 
     * @return true - If refuel occured 
     * @return false - If refuel did not occur
     */
    bool tryRefillFuel();
    
    /**
     * @brief Destroy the Entity Manager object
     */
    ~EntityManager();

private:

    /**
     * @brief Function that checks if two entities are colliding also using the hitboxoverlap function
     * Returns true if hitboxes overlap and the object 1 can collide with object j
     * this means we can add functionality for one object being destroyed but another not. ie: i can collide with j, but not vice versa.
     * @param entity1 - The first entity that is checked for collision
     * @param entity2 - The second entity that is checked for collision
     * @return true - if the entities do collide
     * @return false - if the entities don't collide 
     */
    bool isColliding(const shared_ptr<GameEntity> &entity1, const shared_ptr<GameEntity> &entity2); 
    
    double topBorderHeight_; /*The boarder height of the screen*/
    double bottomBorderHeight_; /*Bottom border height of the screen*/
    double screenWidth_; /*The width of the screen that is visible*/
};

#endif