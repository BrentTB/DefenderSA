#ifndef LANDER
#define LANDER

/**
 * @file Lander.h
 * @brief This file holds the class that controls the lander. 
 */
#include "EnemyEntity.h"

using namespace std;

/**
 * @class Lander 
 * @brief This class is a derived class of EnemyEntity which is also derived from GameEntity. 
 * It overides the functionality to be used for the Lander Entity
 * @see EnemyEntity
 */
class Lander : public EnemyEntity
{
public:
    /**
     * @brief Construct a new Lander object
     * 
     * @param x - The x position of the lander
     * @param y - The y position of the lander 
     * @param direction - The direction the lander is facing
     */
    Lander(const double &x, const double &y, const bool &direction);

    /**
     * @brief The lander tried to kidnap the humanoid
     * 
     * @param humanoid - The humanoid object
     */
    void tryToKidnap(const shared_ptr<GameEntity>& humanoid);

    /**
     * @brief Sets the hasKidnapped variable to true if the humanoid has been kidnapped
     * 
     * @param hasKidnapped - true or false if kidnapped or not
     */
    void hasKidnapped(const bool& hasKidnapped);

    /**
     * @brief Returns whether the humanoid has been kidnapped or not
     * 
     * @return true - has been kidnapped 
     * @return false - has not been kidnapped
     */
    bool hasKidnapped();

    /**
     * @brief Function called if lander with captured humanoid reaches the top of the screen
     */
    void successfullyKidnapped();

    /**
     * @brief Get the Momentum object
     * 
     * @return tuple<double,double> - returns the <speed, angle>
     */
    tuple<double,double> getMomentum();

    /**
     * @brief Destroy the Lander object
     */
    ~Lander();

private:
    /**
     */
    void move(const double &deltaTime) override;
    
    /**
     * @brief Moves the lander towards the humanoid function
     * 
     * @param deltaTime - Change in time
     * @return * void - Updates the positions of the Lander 
     */
    void moveToKidnap(const double &deltaTime);

    /**
     * @brief This checks the Lander FireTimer, if it can fire it calls the entity creator to create LanderLaser
     * @param deltaTime - Change in time
     * @return true - Can fire
     * @return false - Cannot fire
     */
    bool tryFire(const double &deltaTime) override; 
    
    bool hasKidnapped_;               /*Set true if the lander has kidnapped the humanoid*/
    shared_ptr<GameEntity> humanoid_; /*Humanoid entity: is trying to kidnap = true when humanoid_ != nullptr*/
};

#endif
