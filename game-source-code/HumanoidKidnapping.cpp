#include "HumanoidKidnapping.h"

HumanoidKidnapping::HumanoidKidnapping(shared_ptr<EntityManager> entityManager, const double &topBorderHeight, const double &bottomBorderHeight) : entityManager_(entityManager),
                                                                                                                                                   topBorderHeight_(topBorderHeight),
                                                                                                                                                   bottomBorderHeight_(bottomBorderHeight),
                                                                                                                                                   humanoidTimer_(0)
{
}

void HumanoidKidnapping::checkKidnapping(const double &screenPos)
{
    checkKidnappingCollisions();
    checkKidnappingSave();
    checkKidnappingOutOfBounds();
    targetHumanoids(screenPos);
}

void HumanoidKidnapping::checkKidnappingCollisions()
{
    for (auto entity1 : GameEntity::allEntities)
    {
        if (entity1->getType() != EntityList::Humanoid)
            continue;
        for (auto entity2 : GameEntity::allEntities)
        {
            if (!entityManager_->hitboxOverlap(entity1, entity2))
                continue;
            if ((entity2->getType() == EntityList::Player || entity2->getType() == EntityList::PlayerShield) && dpc<Humanoid>(entity1)->isFalling() && !dpc<Player>(entity2)->isSaving())
            {
                dpc<Humanoid>(entity1)->pickedUp(entity2);
                dpc<Player>(entity2)->isSaving(true);
                break;
            }
            else if (entity2->getType() == EntityList::Lander && !dpc<Humanoid>(entity1)->isKidnapped() && !dpc<Lander>(entity2)->hasKidnapped())
            {
                dpc<Humanoid>(entity1)->pickedUp(entity2);
                dpc<Lander>(entity2)->tryToKidnap(entity1);
                dpc<Lander>(entity2)->hasKidnapped(true);
                break;
            }
        }
    }
}

void HumanoidKidnapping::checkKidnappingSave()
{
    for (auto entity1 : GameEntity::allEntities)
    {
        if (entity1->getType() != EntityList::Humanoid)
            continue;
        if (dpc<Humanoid>(entity1)->isKidnapped() == GameEntity::allEntities[0] && get<1>(entity1->getPosition()) < bottomBorderHeight_)
        {
            dpc<Humanoid>(entity1)->putDown();
            dpc<Player>(GameEntity::allEntities[0])->isSaving(false);
        }
    }
}

void HumanoidKidnapping::checkKidnappingOutOfBounds()
{
    for (auto entity1 : GameEntity::allEntities)
    {
        if (entity1->getType() == EntityList::Humanoid && dpc<Humanoid>(entity1)->isFalling() && get<1>(entity1->getPosition()) < bottomBorderHeight_)
        {
            entity1->destroy();
        }
        if (entity1->getType() == EntityList::Lander && dpc<Lander>(entity1)->hasKidnapped() && get<1>(entity1->getPosition()) >= topBorderHeight_)
        {
            dpc<Lander>(entity1)->successfullyKidnapped();
        }
    }
}

void HumanoidKidnapping::targetHumanoids(const double &screenPos)
{
    auto humanoid = shared_ptr<GameEntity>();
    auto lander = shared_ptr<GameEntity>();
    for (auto entity : GameEntity::allEntities)
    {
        if (entity->getType() == EntityList::Lander && !dpc<Lander>(entity)->hasKidnapped())
        {
            lander = entity;
        }
        if (entity->getType() == EntityList::Humanoid && !dpc<Humanoid>(entity)->isKidnapped())
        {
            auto position = entity->getPosition();
            if (entityManager_->onScreen(get<0>(position), get<1>(position), screenPos))
                humanoid = entity;
        }
    }

    const auto elapsedTime = Clock::getGameTime() - humanoidTimer_;
    const auto humanoidDelay = float{10};
    if (elapsedTime > humanoidDelay && humanoid != nullptr && lander != nullptr)
    {
        humanoidTimer_ = Clock::getGameTime();
        dpc<Lander>(lander)->tryToKidnap(humanoid);
    }
}

HumanoidKidnapping::~HumanoidKidnapping() {}