#ifndef ENTITYCREATOR
#define ENTITYCREATOR

/**
 * @file EntityCreator.h
 * @brief This class runs all the entity creation 
 */
#include <vector>
#include "Player.h"
#include "PlayerLaser.h"
#include "Lander.h"
#include "LanderLaser.h"
#include "Bomber.h"
#include "Mine.h"
#include "Asteroid.h"
#include "Humanoid.h"
#include "FuelTank.h"

using namespace std;

/**
 * @class EntityCreator Entitiy Creator class 
 * @brief This class manages all the creation of entities such as players, landers etc.  
 */
class EntityCreator
{
public:
    /**
     * @brief Construct a new Entity Creator object
     * @param topBorderHeight - Top boarder height of the screen
     * @param bottomBorderHeight - Bottom border height of the screen 
     */
    EntityCreator(const double &topBorderHeight, const double &bottomBorderHeight);

    /**
     * @brief Create a Projectiles object from each entity at index fireIndex[i]
     * @param fireIndexes - The index where the object should fire 
     */
    void createProjectiles(const vector<int> &fireIndexes); 

    /**
     * @brief This function tries to create all entites that are random includes making enemies, fuel, humanoids, etc
     * @param deltaTime - The change in time
     * @param randomNumbers - Vector of random numbers 
     */
    void tryRandomEvents(const double &deltaTime, vector<int> randomNumbers = {});

    /**
     * @brief This function tries to level-up and tests if all enemies are destroyed
     * The function also changes maxEnemies_ and spawnedEnemies_
     * @param numEnemiesDestroyed - The number of enemies destroyed 
     * @return true - Returns true if the level increases 
     * @return false - No level increase 
     */
    bool tryLevelUp(const int &numEnemiesDestroyed); 

    /**
     * @brief resets the maxEnemies and spawns a player at the default location (500,500,true)
     */
    void reset();

    /**
     * @brief Destroy the Entity Creator object
     */
    ~EntityCreator();

private:
    /**
     * @brief Tries to create a Humanoid
     * @param deltaTime - The change in time
     * @param randomNumbers - Vector of random numbers
     */
    void tryCreateHumanoid(const double &deltaTime, const vector<int> &randomNumbers);

    /**
     * @brief Tries to create an Asteroid Shower
     * @param deltaTime - The change in time
     * @param randomNumbers - Vector of random numbers
     */
    void tryCreateAsteroidShower(const double &deltaTime, const vector<int> &randomNumbers);

    /**
     * @brief Tries to create the fuel tank
     * @param deltaTime - The change in time
     * @param randomNumbers - Vector of random numbers
     */
    void tryCreateFuelTank(const double &deltaTime, const vector<int> &randomNumbers);

    /**
     * @brief Tries to create a Lander or Bomber enemy
     * @param deltaTime - The change in time
     * @param randomNumbers - Vector of random numbers
     */
    void tryCreateEnemy(const double &deltaTime, const vector<int> &randomNumbers);

    /**
     * @brief Create a Player object
     */
    void createPlayer();

    /**
     * @brief Create a Player Laser object
     * @param parentEntity - The parent entity (Lander or Player)
     */
    void createPlayerLaser(const shared_ptr<GameEntity> &parentEntity);

    /**
     * @brief Create a Lander object
     * @param randomNumbers - Vector of random numbers
     */
    void createLander(const vector<int> &randomNumbers);

    /**
     * @brief Create a Lander Laser object
     * @param parentEntity - The parent entity (Lander or Player)
     */
    void createLanderLaser(const shared_ptr<GameEntity> &parentEntity);

    /**
     * @brief Create a Bomber object
     * @param randomNumbers - Vector of random numbers
     */
    void createBomber(const vector<int> &randomNumbers);

    /**
     * @brief Create a Mine object
     * @param parentEntity - The parent entity (Lander or Player)
     */
    void createMine(const shared_ptr<GameEntity> &parentEntity);

    /**
     * @brief Create a Asteroid object
     * @param randomNumbers - Vector of random numbers
     */
    void createAsteroid(const vector<int> &randomNumbers);

    /**
     * @brief Create a Humanoid object
     * @param randomNumbers - Vector of random numbers
     */
    void createHumanoid(const vector<int> &randomNumbers);

    /**
     * @brief Create a Fuel Tank object
     * @param randomNumbers - Vector of random numbers
     */
    void createFuelTank(const vector<int> &randomNumbers);

    /**
     * @brief Creates a new Vector that is a subset of a given Vector
     * 
     * @param numbers - A vector of integers to fill the new vector
     * @param start - Where the new vector should start
     * @return vector<int> - New Vector made
     */
    vector<int> newVect(const vector<int> &numbers, int start);

    /**
     * @brief Function that finds where the enemy should spawn based on the player's position
     * 
     * @param randomNumbers - Vector of random numbers
     * @return entityPosition - tuple of <x pos, y pos, direction>
     */
    entityPosition enemySpawnPosition(const vector<int> &randomNumbers);

    int maxEnemies_;            /** Max number of enemies there can be */
    int spawnedEnemies_;        /** Number of enemies that have been spawned */
    double asteroidTimer_;      /** The Gametime at which asteroid showers occurs */
    int asteroidCount_;         /** The number of asteroids in the shower */
    double topBorderHeight_;    /** Height players can't enter on the screen */
    double bottomBorderHeight_; /** Bottom border players can't enter */
};

#endif