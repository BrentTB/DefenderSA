#include "FuelTank.h"

FuelTank::FuelTank(const double &x, const double &y, const bool &direction) : GameEntity(x, y, direction),
                                                                              fuelTimer_(Clock::getGameTime() + 10)
{
    direction_ = true;
    width_ = 64 - 32;
    height_ = 64 - 8;
    speed_ = 0;
    defeatScore_ = 0;
    type_ = EntityList::FuelTank;
}

bool FuelTank::update(const double &deltaTime)
{
    if (fuelTimer_ < Clock::getGameTime())
        destroy();
    return false;
}
FuelTank::~FuelTank() {}