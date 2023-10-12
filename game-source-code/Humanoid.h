#ifndef HUMANOID
#define HUMANOID

/**
 * @file Humanoid.h
 * @brief File that manages the humanoid class
 */
#include "GameEntity.h"
#include "Lander.h"

using namespace std;

/**
 * @class Humanoid
 * @brief This class runds the humanoid functionality and is derived from GameEntity
 * 
 * @see GameEntity
 * 
 */
class Humanoid : public GameEntity
{
public:
    /**
     * @brief Construct a new Humanoid object
     * 
     * @param x - The x position of the humanoid
     * @param y - The y position of the humanoid
     * @param direction - The direction of the humanoid
     */
    Humanoid(const double &x, const double &y, const bool &direction);

    /**
     * @brief Performs move, try fire, anything that needs to be done per frame. If it should fire, returns true
     * 
     * @param deltaTime - The amount of time passed 
     * @return true - If the entity should fire (Humanoid will never fire)
     * @return false - Entity shouldn't fire
     */
    bool update(const double &deltaTime) override;

    /**
     * @brief If a humanoid is picked up, the GameEntity is set as kidnapperEntity
     * 
     * @param kidnapperEntity - The kidnapper which is the Lander 
     */
    void pickedUp(const shared_ptr<GameEntity>& kidnapperEntity);

    /**
     * @brief This function would make the GameEntity a KidnapperEntity
     * 
     * @return shared_ptr<GameEntity> 
     */
    shared_ptr<GameEntity> isKidnapped();

    /**
     * @brief This sets the humanoid to be 'on the ground'
     */
    void putDown();

    /**
     * @brief The humanoid would not be ontheground and would not be kidnapped
     * 
     * @return true - if the humanoid is falling
     * @return false - if the humanoid isn't firing
     */
    bool isFalling();
    
    /**
     * @brief Destroy the Humanoid object
     */
    virtual ~Humanoid();

private:
    /**
     * @brief This moves the sprite. The player's location can always be accessed through the static vector
     * 
     * @param deltaTime - Change in time
     */
    void move(const double &deltaTime);   

    /**
     * @brief This is the humanoid falling after the lander is destroyed
     * 
     * @param deltaTime - Change in time
     */
    void fall(const double &deltaTime);

    bool isOnGround_;                           /*True if the humanoid is on the ground*/
    shared_ptr<GameEntity> kidnapperEntity_;    /*Entity set as a kidnapperEntity once kidnapped*/
    double moveTimer_;                          /*how long the humanoid moves for left to right*/
};

#endif