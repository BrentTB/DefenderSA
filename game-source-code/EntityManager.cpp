#include "EntityManager.h"

EntityManager::EntityManager(const double &topBorderHeight, const double &bottomBorderHeight, const double &screenWidth) : topBorderHeight_(topBorderHeight),
                                                                                                                           bottomBorderHeight_(bottomBorderHeight),
                                                                                                                           screenWidth_(screenWidth)
{
}

bool EntityManager::tryRefillFuel()
{
    for (auto entity : GameEntity::allEntities)
    {
        if (entity->getType() == EntityList::FuelTank && hitboxOverlap(entity, GameEntity::allEntities[0]))
        {
            entity->destroy();
            return true;
        }
    }
    return false;
}

void EntityManager::checkEntityCollisions()
{
    for (auto entity1 : GameEntity::allEntities)
    {
        for (auto entity2 : GameEntity::allEntities)
        {
            if (isColliding(entity1, entity2))
                entity1->destroy();
        }
    }
}

void EntityManager::checkOffScreenProjectiles(const double &screenPos)
{
    for (auto entity : GameEntity::allEntities)
    {
        const auto type = entity->getType();
        if (type == EntityList::PlayerLaser || type == EntityList::LanderLaser)
        {
            if (!onScreen(get<0>(entity->getPosition()), get<1>(entity->getPosition()), screenPos))
                entity->destroy();
        }
        else if (type == EntityList::Asteroid)
        {
            if (get<1>(entity->getPosition()) < bottomBorderHeight_)
                entity->destroy();
        }
    }
}

bool EntityManager::hitboxOverlap(const shared_ptr<GameEntity> &entity1, const shared_ptr<GameEntity> &entity2)
{
    const auto position1 = entity1->getPosition();
    const auto position2 = entity2->getPosition();
    const auto size1 = entity1->getSize();
    const auto size2 = entity2->getSize();
    const auto xDifference = abs(get<0>(position1) - get<0>(position2));
    const auto yDifference = abs(get<1>(position1) - get<1>(position2));
    const auto xSize = (get<0>(size1) + get<0>(size2)) / 2;
    const auto ySize = (get<1>(size1) + get<1>(size2)) / 2;

    return xDifference <= xSize && yDifference <= ySize && entity1 != entity2;
}

bool EntityManager::isColliding(const shared_ptr<GameEntity> &entity1, const shared_ptr<GameEntity> &entity2)
{
    if (!hitboxOverlap(entity1, entity2))
        return false;

    const auto type1 = entity1->getType();
    const auto type2 = entity2->getType();

    if (type1 == EntityList::Player)
    {
        return type2 != EntityList::PlayerLaser && type2 != EntityList::Humanoid && type2 != EntityList::FuelTank;
    }
    if (type1 == EntityList::PlayerLaser)
    {
        return type2 != EntityList::Player && type2 != EntityList::PlayerShield && type2 != EntityList::PlayerLaser && type2 != EntityList::Mine && type2 != EntityList::FuelTank;
    }
    if (type1 == EntityList::PlayerShield)
        return false;

    if (type1 == EntityList::Lander || type1 == EntityList::Bomber || type1 == EntityList::LanderLaser)
    {
        return type2 == EntityList::Player || type2 == EntityList::PlayerShield || type2 == EntityList::PlayerLaser || type2 == EntityList::Asteroid;
    }

    if (type1 == EntityList::Humanoid)
    {
        return type2 == EntityList::PlayerLaser;
    }

    if (type1 == EntityList::Mine)
    {
        return type2 == EntityList::Player || type2 == EntityList::PlayerShield;
    }

    if (type1 == EntityList::Asteroid)
    {
        return type2 != EntityList::Mine && type2 != EntityList::LanderLaser && type2 != EntityList::Asteroid && type2 != EntityList::Humanoid && type2 != EntityList::FuelTank;
    }

    if (type1 == EntityList::FuelTank)
        return false;

    assert(false);
    return false;
}

bool EntityManager::onScreen(const double &x, const double &y, const double &screenPos)
{
    return !(y > topBorderHeight_ || y < bottomBorderHeight_ || x < screenPos || x > screenPos + screenWidth_);
}

EntityManager::~EntityManager() {}