#include "Clock.h"

sf::Clock Clock::gameClock_;
sf::Clock Clock::FPSClock_;
float Clock::pauseTime_ = 0;
float Clock::sumPauseTime_ = 0;

void Clock::reset()
{
    gameClock_.restart();
    FPSClock_.restart();
    pauseTime_ = 0;
    sumPauseTime_ = 0;
}

float Clock::getGameTime()
{
    return gameClock_.getElapsedTime().asSeconds() - sumPauseTime_;
}

float Clock::getDeltaTime()
{
    return FPSClock_.restart().asSeconds();
}

void Clock::setGameIsPaused(const int &paused)
{
    if (paused)
    {
        pauseTime_ = gameClock_.getElapsedTime().asSeconds();
    }
    else
    {
        pauseTime_ = gameClock_.getElapsedTime().asSeconds() - pauseTime_;
        sumPauseTime_ += pauseTime_;
    }
}

void Clock::addTime(const float &time)
{
    sumPauseTime_ -= time;
}

Clock::~Clock() {}