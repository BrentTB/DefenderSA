#include "PlayerLaser.h"

PlayerLaser::PlayerLaser(const double &x, const double &y, const bool &direction) : ProjectileEntity(x, y, direction)
{
    width_ = 40;
    height_ = 6;
    speed_ = 2200;
    type_ = EntityList::PlayerLaser;
    angle_ = direction_ ? 0 : M_PI;
}

PlayerLaser::~PlayerLaser() {}