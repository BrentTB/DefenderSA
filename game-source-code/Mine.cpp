#include "Mine.h"

Mine::Mine(const double &x, const double &y, const bool &direction) : ProjectileEntity(x, y, direction)
{
    width_ = 64 - 24;
    height_ = 64 - 40;
    speed_ = 0;
    type_ = EntityList::Mine;
    angle_ = 0;
}

Mine::~Mine() {}