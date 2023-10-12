#include "ProjectileEntity.h"

ProjectileEntity::ProjectileEntity(const double &x, const double &y, const bool &direction) : GameEntity(x, y, direction)
{
    defeatScore_ = 0;
}

bool ProjectileEntity::update(const double &deltaTime)
{
    move(deltaTime);
    return false;
}

void ProjectileEntity::move(const double &deltaTime)
{
    x_ += cos(angle_) * speed_ * deltaTime;
    y_ += sin(angle_) * speed_ * deltaTime;
}

double ProjectileEntity::getTiltAngle()
{
    return angle_;
}

ProjectileEntity::~ProjectileEntity() {}