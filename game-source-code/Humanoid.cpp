#include "Humanoid.h"

Humanoid::Humanoid(const double &x, const double &y, const bool &direction) : GameEntity(x, y, direction),
                                                                              isOnGround_(true),
                                                                              moveTimer_(0)
{
    width_ = 64 - 30;
    height_ = 64 - 18;
    type_ = EntityList::Humanoid;
    defeatScore_ = -80;
}

bool Humanoid::update(const double &deltaTime)
{
    if (kidnapperEntity_ != nullptr)
    {
        if (kidnapperEntity_->isDestroyed())
        {
            isOnGround_ = false;
            if (kidnapperEntity_->getType() == EntityList::Lander)
            {
                auto momentum = dynamic_pointer_cast<Lander>(kidnapperEntity_)->getMomentum();
                speed_ = get<0>(momentum);
                angle_ = get<1>(momentum);
            }
            kidnapperEntity_ = nullptr;
            fall(deltaTime);
        }
        else
        {
            const auto kidnapperPosition = kidnapperEntity_->getPosition();
            const auto kidnapperSize = kidnapperEntity_->getSize();
            x_ = get<0>(kidnapperPosition);
            y_ = get<1>(kidnapperPosition) - (height_ + get<1>(kidnapperSize)) / 2;
        }
    }
    else if (isOnGround_)
        move(deltaTime);
    else
        fall(deltaTime);

    return false;
}

shared_ptr<GameEntity> Humanoid::isKidnapped()
{
    return kidnapperEntity_;
}

void Humanoid::pickedUp(const shared_ptr<GameEntity> &kidnapperEntity)
{
    kidnapperEntity_ = kidnapperEntity;
}

void Humanoid::putDown()
{
    isOnGround_ = true;
    kidnapperEntity_ = nullptr;
}

void Humanoid::fall(const double &deltaTime)
{
    const auto minSpeed = double{10};
    if (speed_ < minSpeed && angle_ != M_PI / 2)
    {
        angle_ = M_PI / 2;
        speed_ = 0;
    }

    const auto acceleration = double{80};
    if (speed_ > 0 && speed_ - acceleration * deltaTime <= 0)
    {
        angle_ = M_PI - angle_;
    }

    speed_ -= acceleration * deltaTime;

    x_ += cos(angle_) * speed_ * deltaTime;
    y_ += sin(angle_) * speed_ * deltaTime;

    if (y_ >= topBorder_)
    {
        y_ = topBorder_;
        speed_ = 0;
        angle_ = M_PI - angle_;
    }
}

bool Humanoid::isFalling()
{
    return !isOnGround_;
}

void Humanoid::move(const double &deltaTime)
{
    const auto walkSpeed = double{20};
    if (moveTimer_ < Clock::getGameTime())
    {
        moveTimer_ = 3 + Clock::getGameTime();
        direction_ = !direction_;
    }

    x_ += (direction_ ? 1 : -1) * walkSpeed * deltaTime;
}

Humanoid::~Humanoid() {}