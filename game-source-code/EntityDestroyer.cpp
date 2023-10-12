#include "EntityDestroyer.h"

EntityDestroyer::EntityDestroyer() {}

void EntityDestroyer::removeEntityType(const EntityList &entityType)
{
    for (auto itr = end(GameEntity::allEntities); itr != begin(GameEntity::allEntities);)
    {
        itr--;
        if ((*itr)->getType() == entityType)
        {
            GameEntity::allEntities.erase(itr);
        }
    }
}

void EntityDestroyer::removeAllEntities()
{
    for (auto itr = end(GameEntity::allEntities); itr != begin(GameEntity::allEntities);)
    {
        GameEntity::allEntities.erase(--itr);
    }
}

tuple<int, int> EntityDestroyer::removeDestroyedEntities()
{
    auto numEnemiesDestroyed = int{0};
    auto score = int{0};
    for (auto itr = GameEntity::allEntities.end(); itr != GameEntity::allEntities.begin() + 1;)
    {
        itr--;
        if ((*itr)->isDestroyed())
        {
            if ((*itr)->getType() == EntityList::Lander || (*itr)->getType() == EntityList::Bomber)
            {
                numEnemiesDestroyed++;
            }
            score += (*itr)->getDefeatScore();
            GameEntity::allEntities.erase(itr);
        }
    }
    return {numEnemiesDestroyed, score};
}

EntityDestroyer::~EntityDestroyer()
{
    removeAllEntities();
    Clock::reset();
}