#include "Bomber.h"

Bomber::Bomber(const double &x, const double &y, const bool &direction) : EnemyEntity(x, y, direction),
                                                                          target_(x_, y_, true),
                                                                          atTarget_(false)
{
    width_ = 64 - 16;
    height_ = 64 - 20; 
    type_ = EntityList::Bomber;
    defeatScore_ = 15;
}

void Bomber::move(const double &deltaTime)
{
    const auto targetDistance = double{175};
    const auto minDist = double{15};

    const auto position = GameEntity::allEntities[0]->getPosition();
    const auto gameTime = Clock::getGameTime();

    if (distanceFromTarget(get<0>(target_), get<1>(target_)) < minDist)
    {
        get<0>(target_) = get<0>(position) + 2 * targetDistance * cos(gameTime * 5 / 3 + M_PI / 2);
        get<1>(target_) = get<1>(position) + targetDistance * cos(gameTime * 5);
        if (get<1>(target_) > topBorder_ || get<1>(target_) < bottomBorder_)
        {
            get<1>(target_) = get<1>(position) - targetDistance * cos(gameTime * 5);
        }
        atTarget_ = true;
    }

    const auto angleDifference = getAngleDifference(target_);
    const auto acceleration = double{40};
    const auto maxSpeed = double{120};
    
    angle_ += angleDifference * deltaTime + M_PI * sin(gameTime) * deltaTime / 3;
    speed_ += (abs(angleDifference) < M_PI / 2 ? acceleration : -acceleration) * deltaTime;
    speed_ = speed_ > 0 ? min(maxSpeed, speed_) : max(-maxSpeed, speed_);

    setPosition(deltaTime);
}

bool Bomber::tryFire(const double &deltaTime)
{
    if (atTarget_)
    {
        atTarget_ = false;
        return true;
    }
    return false;
}

Bomber::~Bomber() {}