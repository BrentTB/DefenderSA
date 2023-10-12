#ifndef ENTITYLIST
#define ENTITYLIST

/**
 * @file EntityList.h
 * @brief Enum class of the entities 
 * 
 */

/**
 * @class EntityList  
 * @brief This class is an enum which holds the possible entities in the game
 * 
 */
enum class EntityList
{
	/**
	 * @enum EntityList::EntityList 
	 * 
	 */
	Player = 0, /*< The main player in the game, represented by a red car */
	PlayerShield, /*< The player above with a shield on*/
	PlayerLaser, /*< The players laser used to shoot enemies */
	Lander, /*< The main enemy in the game, represented by a taxi */
	LanderLaser, /*< The laser that shoots at the player */
	Bomber, /*< The bomber that drops mines, represented by the "Eishkom" logo*/
	Mine, /*< The mine is a enemy that doesn't move but destroys the player if 'driven' into. Represented as a pothole */
	Asteroid, /*< Asteroids shower from the top of the screen, and destroys everything in its path. Represented as a stop sign*/
	Humanoid, /*< Humanoids are captured by the lander and saved by the player. Represented by a pile of money */
	FuelTank /*< Fuel tank for player to refill fuel. */
};

#endif