#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(const double &x, const double &y, const bool &direction) : GameEntity(x, y, direction),
                                                                                    fireTimer_(0.0f)
{
    speed_ = 0;
}

bool EnemyEntity::update(const double &deltaTime)
{
    move(deltaTime);
    return tryFire(deltaTime);
}

void EnemyEntity::setPosition(const double &deltaTime)
{
    direction_ = speed_ * cos(angle_) > 0;

    x_ += speed_ * cos(angle_) * deltaTime;
    y_ += speed_ * sin(angle_) * deltaTime;

    y_ = max(y_, bottomBorder_ * 1.0);
    y_ = min(y_, topBorder_ * 1.0);
}

double EnemyEntity::getAngleDifference(const entityPosition &position)
{
    const auto desiredAngle = double{atan2(get<1>(position) - y_, get<0>(position) - x_)};
    const auto minSpeed = double{10};
    if (speed_ < minSpeed)
    {
        angle_ = desiredAngle;
    }

    auto angleDifference = desiredAngle - angle_;

    if (angleDifference > M_PI)
    {
        angleDifference -= 2 * M_PI;
    }
    else if (angleDifference < -M_PI)
    {
        angleDifference += 2 * M_PI;
    }
    return angleDifference;
}

double EnemyEntity::distanceFromTarget(const double &x, const double &y)
{
    return sqrt((x_ - x) * (x_ - x) + (y_ - y) * (y_ - y));
}

EnemyEntity::~EnemyEntity() {}