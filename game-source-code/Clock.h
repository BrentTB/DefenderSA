#ifndef CLOCK
#define CLOCK

/**
 * @file Clock.h
 * @brief This file manages the clock functionality. The clock controls the time of the game. 
 * It starts when the game begins, stops when the game pauses and is restarted when the game begins each time.  
 * 
 */
#include <SFML/Graphics.hpp>

using namespace std;

/**
 * @brief Clock class
 * This class manages the clock object.
 */
class Clock
{
public:
    /**
     * @brief Construct a new Clock object
     */
    Clock(){};
    
    /**
     * @brief Get the Game Time
     * @return float of the time the game is at
     */
    static float getGameTime();
   
    /**
     * @brief Get the Delta Time
     * @return float of the change in time
     */
    static float getDeltaTime();
   
    /**
     * @brief Set the Game Is Paused object
     * This stops the game clock when the game is paused
     * @param paused - time paused for
     */
    static void setGameIsPaused(const int& paused);
   
    /**
     * @brief Function that adds time to the game after being paused. 
     * @param time - time added after being pasued 
     */
    static void addTime(const float& time);
   
    /**
     * @brief Resets the clock object. 
     */
    static void reset();

    /**
     * @brief Destroy the Clock object
     */
    ~Clock();

private:
    /**
     * @brief SFML clock object 
     */
    static sf::Clock gameClock_;

    /**
     * @brief float to determine how long the game is paused 
     */
    static float pauseTime_;

    /**
     * @brief float that stored the amount of time paused
     */
    static float sumPauseTime_;

    /**
     * @brief SFML clock for the frames per second
     */
    static sf::Clock FPSClock_;
};

#endif