#include "Asteroid.h"

Asteroid::Asteroid(const double &x, const double &y, const bool &direction) : ProjectileEntity(x, y, direction)
{
    width_ = 64 - 26;
    height_ = 64 - 26;
    speed_ = 250;
    type_ = EntityList::Asteroid;
    angle_ = -M_PI / 2 + (direction_ ? -M_PI / 8 : M_PI / 8);
}

Asteroid::~Asteroid() {}
