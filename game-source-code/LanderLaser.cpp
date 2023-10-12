#include "LanderLaser.h"

LanderLaser::LanderLaser(const double &x, const double &y, const bool &direction) : ProjectileEntity(x, y, direction)
{
    width_ = 16;
    height_ = 6;
    speed_ = 200;
    type_ = EntityList::LanderLaser;

    const auto player = GameEntity::allEntities[0];
    angle_ = atan2(get<1>(player->getPosition()) - y_, get<0>(player->getPosition()) - x_);
}

LanderLaser::~LanderLaser() {}