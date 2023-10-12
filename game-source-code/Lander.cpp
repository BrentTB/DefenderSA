#include "Lander.h"

Lander::Lander(const double &x, const double &y, const bool &direction) : EnemyEntity(x, y, direction),
                                                                          hasKidnapped_(false),
                                                                          humanoid_(nullptr)
{
    width_ = 128 - 18;
    height_ = 64 - 12;
    type_ = EntityList::Lander;
    defeatScore_ = 10;
    fireTimer_ = Clock::getGameTime();
}

tuple<double, double> Lander::getMomentum()
{
    return {speed_, angle_};
}

void Lander::move(const double &deltaTime)
{
    if (humanoid_ != nullptr)
    {
        if (humanoid_->isDestroyed())
        {
            humanoid_ = nullptr;
            hasKidnapped_ = false;
        }
        else
        {
            moveToKidnap(deltaTime);
            return;
        }
    }

    const auto position = GameEntity::allEntities[0]->getPosition();
    const auto dist = distanceFromTarget(get<0>(position), get<1>(position));
    const auto angleDifference = getAngleDifference(position);

    const auto stayDistance = double{400};
    const auto acceleration = double{80};
    const auto maxSpeed = double{200};
    const auto accelerationFactor = double{1000};

    angle_ += angleDifference * deltaTime;
    speed_ += (abs(angleDifference) < M_PI / 2 ? acceleration : -2 * acceleration) * (dist > stayDistance ? 1 : -1) * deltaTime * accelerationFactor / dist;
    speed_ = speed_ > 0 ? min(maxSpeed, speed_) : max(-maxSpeed, speed_);

    setPosition(deltaTime);
}

void Lander::moveToKidnap(const double &deltaTime)
{
    auto acceleration = double{80};
    auto maxSpeed = double{200};

    auto targetPosition = humanoid_->getPosition();
    if (hasKidnapped_)
    {
        acceleration = double{40};
        maxSpeed = double{100};
        targetPosition = tuple{x_, 3000, true};
    }

    const auto angleDifference = getAngleDifference(targetPosition);

    angle_ += angleDifference * deltaTime;
    speed_ += (abs(angleDifference) < M_PI / 2 ? acceleration : -acceleration) * deltaTime;
    speed_ = speed_ > 0 ? min(maxSpeed, speed_) : max(-maxSpeed, speed_);

    setPosition(deltaTime);
}

bool Lander::tryFire(const double &deltaTime)
{
    if (humanoid_ != nullptr)
        return false;
    const auto elapsedTime = Clock::getGameTime() - fireTimer_;
    const auto fireDelay = float{3.0f};
    if (elapsedTime < fireDelay)
        return false;
    fireTimer_ = Clock::getGameTime();
    return true;
}

void Lander::tryToKidnap(const shared_ptr<GameEntity> &humanoid)
{
    humanoid_ = humanoid;
    hasKidnapped_ = false;
}

void Lander::hasKidnapped(const bool &hasKidnapped)
{
    hasKidnapped_ = hasKidnapped;
}

bool Lander::hasKidnapped()
{
    return hasKidnapped_;
}

void Lander::successfullyKidnapped()
{
    humanoid_->destroy();
    destroy();
}

Lander::~Lander() {}