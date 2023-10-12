#ifndef ENTITYDESTROYER
#define ENTITYDESTROYER

/**
 * @file EntityDestroyer.h
 * @brief File that controls the destruction of entities
 */
#include "GameEntity.h"

using namespace std;
/**
 * @class EntityDestoyer
 * @brief This class manages the destruction of entities when they are no longer needed 
 * 
 */
class EntityDestroyer
{
public:
    /**
     * @brief Construct a new Entity Destroyer object. This object allows entities do be destroyed
     * 
     */
    EntityDestroyer();

    /**
     * @brief This function removes the entity if isDestroyed is true. Returns the number of enemies (not lasers/bombs) that are destroyed, and the score that must be added
     * 
     * @return tuple<int, int> - The number of enemies destroyed
     */
    tuple<int, int> removeDestroyedEntities(); 

    /**
     * @brief This function removes a specific type of entity
     * 
     * @param entityType - The type of entity being destroyed 
     */
    void removeEntityType(const EntityList& entityType); 

    /**
     * @brief This function removes all entities 
     * 
     */
    void removeAllEntities(); 

    /**
     * @brief Destroy the Entity Destroyer object
     * 
     */
    ~EntityDestroyer();
};

#endif