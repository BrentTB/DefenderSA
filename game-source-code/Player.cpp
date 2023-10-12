#include "Player.h"

Player::Player(const double &x, const double &y, const bool &direction) : GameEntity(x, y, direction),
                                                                          fireDelay_(0.2f),
                                                                          fireTimer_(-1.0f),
                                                                          shieldCount_(3),
                                                                          shieldTimer_(0.0f),
                                                                          fuel_(100),
                                                                          isSaving_(false)
{
    width_ = 128 - 48;
    height_ = 64 - 36;
    speed_ = 0;
    defeatScore_ = 0;
    type_ = EntityList::Player;
}

void Player::setUserInput(const map<UserInput, bool> &userInput)
{
    userInput_.clear();
    userInput_ = userInput;
}

bool Player::update(const double &deltaTime)
{
    changeShield(userInput_[UserInput::KeyEnter]);
    if (fuel_ > 0)
        move(deltaTime);
    else
        fall(deltaTime);
    return tryFire(deltaTime);
}

void Player::refillFuel()
{
    fuel_ = 100;
}

void Player::fall(const double &deltaTime)
{
    const auto acceleration = double{30};
    const auto fallFactor = int{1};
    if (speed_ < 0)
        speed_ = -speed_;

    angle_ = ((1 - fallFactor * deltaTime) * angle_ + fallFactor * deltaTime * (-M_PI / 2));

    speed_ += acceleration * deltaTime;
    x_ += cos(angle_) * speed_ * deltaTime;
    y_ += sin(angle_) * speed_ * deltaTime;

    if (y_ < bottomBorder_)
        destroy();
}

void Player::changeShield(const bool &shieldOn)
{
    const auto shieldLength = float{5.0f};
    const auto elapsedTime = Clock::getGameTime() - shieldTimer_;

    if (type_ == EntityList::PlayerShield && elapsedTime > shieldLength)
    {
        setShield(false);
    }

    if (type_ == EntityList::Player && shieldCount_ > 0 && shieldOn)
    {
        shieldTimer_ = Clock::getGameTime();
        shieldCount_--;
        setShield(true);
    }
}

void Player::setShield(const bool &shieldOn)
{
    if (shieldOn)
        type_ = EntityList::PlayerShield;
    else
        type_ = EntityList::Player;
}

void Player::isSaving(const bool &isSaving)
{
    isSaving_ = isSaving;
}

bool Player::isSaving()
{
    return isSaving_;
}

void Player::move(const double &deltaTime)
{
    const auto verticalDistance = double{380};
    const auto acceleration = double{580};
    const auto deceleration = double{420};
    const auto brakingFactor = double{2.2};
    const auto maxSpeed = double{600};
    const auto minSpeed = double{30};
    const auto fuelLoss = int(3);

    if (userInput_[UserInput::KeyW] || userInput_[UserInput::KeyA] || userInput_[UserInput::KeyS] || userInput_[UserInput::KeyD])
    {
        fuel_ -= deltaTime * fuelLoss;
    }

    if (userInput_[UserInput::KeyW])
    {
        y_ += verticalDistance * deltaTime;
    }
    else if (userInput_[UserInput::KeyS])
    {
        y_ -= verticalDistance * deltaTime;
    }

    if (userInput_[UserInput::KeyD])
    {
        speed_ += (speed_ > 0 ? 1 : brakingFactor) * acceleration * deltaTime;
        speed_ = min(speed_, maxSpeed);
        direction_ = true;
    }
    else if (userInput_[UserInput::KeyA])
    {
        speed_ -= (speed_ < 0 ? 1 : brakingFactor) * acceleration * deltaTime;
        speed_ = max(speed_, -maxSpeed);
        direction_ = false;
    }
    else
    {
        speed_ += (speed_ > 0 ? -1 : 1) * deceleration * deltaTime;
        if (abs(speed_) < minSpeed)
        {
            speed_ = 0;
        }
    }
    x_ += speed_ * deltaTime;
    angle_ = speed_ > 0 ? 0 : -M_PI;

    y_ = max(y_, bottomBorder_ * 1.0);
    y_ = min(y_, topBorder_ * 1.0);
}

void Player::levelUp()
{
    shieldCount_ = 3;
}

bool Player::tryFire(const double &deltaTime)
{
    const auto elapsedTime = Clock::getGameTime() - fireTimer_;

    if ( elapsedTime >= fireDelay_ && userInput_[UserInput::KeySpace])
    {
        fireTimer_ = Clock::getGameTime();
        return true;
    }
    return false;
}

tuple<int, double> Player::getPlayerInformation()
{
    return {shieldCount_, fuel_};
}

Player::~Player()
{
}