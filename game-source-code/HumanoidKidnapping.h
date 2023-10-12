#ifndef HUMANOIDKIDNAPPING
#define HUMANOIDKIDNAPPING

/**
 * @file HumanoidKidnapping.h
 * @brief Manages the humanoid kidnapping class
 */
#include <memory>
#include "EntityList.h"
#include "EntityManager.h"
#include "Humanoid.h"
#include "Player.h"
#include "Lander.h"

using namespace std;
#define dpc dynamic_pointer_cast

/**
 * @class HumanoidKidnapping
 * @brief This class holds functions that are used to kidnap the humanoid. The object is called in the humanoid class to seperate concerns.
 */
class HumanoidKidnapping
{
public:
    /**
     * @brief Construct a new Humanoid Kidnapping object
     * 
     * @param entityManager - The shared pointer to the entity manager object 
     * @param topBorderHeight - The top border of the screen that is not playable
     * @param bottomBorderHeight - The bottom border of the screen that is not playable
     */
    HumanoidKidnapping(shared_ptr<EntityManager> entityManager, const double &topBorderHeight, const double &bottomBorderHeight);

    /**
     * @brief This function call sall the private functions and checks if the humanoid has been kidnapped or not.
     * 
     * @param screenPos - The current position of the screen 
     */
    void checkKidnapping(const double &screenPos);

    /**
     * @brief Destroy the Humanoid Kidnapping object
     */
    ~HumanoidKidnapping();

private:
    /**
     * @brief Checks if any entity has collided with the humanoid (for save and capture)
     */
    void checkKidnappingCollisions();

    /**
     * @brief Checks if the humanoid has been saved 
     */
    void checkKidnappingSave();

    /**
     * @brief Checks if the kidnapping goes out of the screen bounds
     */
    void checkKidnappingOutOfBounds();

    /**
     * @brief Function that shows which entities are to capture which. 
     * 
     * @param screenPos - The current position of the screen 
     */
    void targetHumanoids(const double &screenPos);

    /**
     * @brief Checks collisions and deletes entites
     */
    shared_ptr<EntityManager> entityManager_;
    float humanoidTimer_;           /*Amount of time the humanoid has been kidnapped for*/
    double topBorderHeight_;        /*The top bounds of the screen (unplayable area)*/
    double bottomBorderHeight_;     /*The bottom border of the screen (unplayable area)*/
};

#endif