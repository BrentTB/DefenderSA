#include "EntityCreator.h"

EntityCreator::EntityCreator(const double &topBorderHeight, const double &bottomBorderHeight) : topBorderHeight_(topBorderHeight),
                                                                                                bottomBorderHeight_(bottomBorderHeight),
                                                                                                asteroidTimer_(-1),
                                                                                                asteroidCount_(0),
                                                                                                spawnedEnemies_(0),
                                                                                                maxEnemies_(20)
{
}

void EntityCreator::tryRandomEvents(const double &deltaTime, vector<int> randomNumbers)
{
    while (randomNumbers.size() < 14)
    {
        randomNumbers.push_back(rand());
    }
    tryCreateHumanoid(deltaTime, randomNumbers);
    tryCreateAsteroidShower(deltaTime, newVect(randomNumbers, 3));
    tryCreateFuelTank(deltaTime, newVect(randomNumbers, 7));
    if (spawnedEnemies_ < maxEnemies_)
        tryCreateEnemy(deltaTime, newVect(randomNumbers, 9));
}

void EntityCreator::createProjectiles(const vector<int> &fireIndexes)
{
    for (auto index : fireIndexes)
    {
        auto parentEntity = GameEntity::allEntities[index];
        switch (parentEntity->getType())
        {
        case EntityList::Player:
        case EntityList::PlayerShield:
            createPlayerLaser(parentEntity);
            break;
        case EntityList::Lander:
            createLanderLaser(parentEntity);
            break;
        case EntityList::Bomber:
            createMine(parentEntity);
            break;
        default:
            assert(false);
            break;
        }
    }
}

bool EntityCreator::tryLevelUp(const int &numEnemiesDestroyed)
{
    if (numEnemiesDestroyed >= maxEnemies_)
    {
        spawnedEnemies_ = 0;
        maxEnemies_ += 10;
        return true;
    }
    return false;
}

void EntityCreator::reset()
{
    maxEnemies_ = 20;
    spawnedEnemies_ = 0;
    asteroidCount_ = 0;
    asteroidTimer_ = 0;
    createPlayer();
}

void EntityCreator::tryCreateEnemy(const double &deltaTime, const vector<int> &randomNumbers)
{
    const auto landerChance_ = (20 + maxEnemies_ / 2) * 1000 * deltaTime;
    const auto bomberChance_ = maxEnemies_ * 1000 * deltaTime;
    const auto totalChance = landerChance_ + bomberChance_;
    const auto randomNumber = double{(randomNumbers[0] % 100000) * 1.0};
    if (randomNumber < totalChance)
    {
        spawnedEnemies_++;
        if (randomNumber <= landerChance_)
        {
            createLander(newVect(randomNumbers, 1));
        }
        else
        {
            createBomber(newVect(randomNumbers, 1));
        }
    }
}

void EntityCreator::tryCreateHumanoid(const double &deltaTime, const vector<int> &randomNumbers)
{
    const auto humanoidChance = 0.3 * maxEnemies_ * 1000 * deltaTime;
    const auto randomNumber = double{(randomNumbers[0] % 100000) * 1.0};
    if (randomNumber < humanoidChance)
    {
        createHumanoid(newVect(randomNumbers, 1));
    }
}

void EntityCreator::tryCreateAsteroidShower(const double &deltaTime, const vector<int> &randomNumbers)
{
    const auto asteroidShowerChance = 0.1 * maxEnemies_ * 1000 * deltaTime;
    const auto randomNumber = double{(randomNumbers[0] % 100000) * 1.0};
    if (randomNumber < asteroidShowerChance)
    {
        asteroidCount_ += randomNumbers[1] % 4 + 4;
    }

    const auto elapsedTime = Clock::getGameTime() - asteroidTimer_;
    const auto asteroidDelay = double{0.3};
    if (asteroidCount_ > 0 && elapsedTime > asteroidDelay)
    {
        asteroidCount_--;
        asteroidTimer_ = Clock::getGameTime();

        createAsteroid(newVect(randomNumbers, 2));
    }
}

void EntityCreator::tryCreateFuelTank(const double &deltaTime, const vector<int> &randomNumbers)
{
    const auto fuelChance = 10 * 1000 * deltaTime;
    const auto randomNumber = double{(randomNumbers[0] % 100000) * 1.0};
    if (randomNumber < fuelChance)
    {
        createFuelTank(newVect(randomNumbers, 1));
    }
}

void EntityCreator::createPlayer()
{
    EnemyEntity::allEntities.push_back(make_shared<Player>(1600.0 / 3, 450, true));
}

void EntityCreator::createPlayerLaser(const shared_ptr<GameEntity> &parentEntity)
{
    const auto position = parentEntity->getPosition();
    const auto newX = get<0>(position) + (get<2>(position) ? 1 : -1) * 40;
    EnemyEntity::allEntities.push_back(make_shared<PlayerLaser>(newX, get<1>(position), get<2>(position)));
}

void EntityCreator::createLander(const vector<int> &randomNumbers)
{
    const auto position = enemySpawnPosition(randomNumbers);
    EnemyEntity::allEntities.push_back(make_shared<Lander>(get<0>(position), get<1>(position), get<2>(position)));
}

void EntityCreator::createLanderLaser(const shared_ptr<GameEntity> &parentEntity)
{
    const auto position = parentEntity->getPosition();
    const auto newX = get<0>(position) + (get<2>(position) ? 1 : -1) * 55;
    EnemyEntity::allEntities.push_back(make_shared<LanderLaser>(newX, get<1>(position), get<2>(position)));
}

void EntityCreator::createBomber(const vector<int> &randomNumbers)
{
    const auto position = enemySpawnPosition(randomNumbers);
    EnemyEntity::allEntities.push_back(make_shared<Bomber>(get<0>(position), get<1>(position), get<2>(position)));
}

void EntityCreator::createMine(const shared_ptr<GameEntity> &parentEntity)
{
    const auto position = parentEntity->getPosition();
    EnemyEntity::allEntities.push_back(make_shared<Mine>(get<0>(position), get<1>(position), get<2>(position)));
}

void EntityCreator::createAsteroid(const vector<int> &randomNumbers)
{
    const auto direction = randomNumbers[0] % 2;
    const auto x = get<0>(GameEntity::allEntities[0]->getPosition()) + (direction ? 1 : -1) * (randomNumbers[1] % 800 + 100);
    EnemyEntity::allEntities.push_back(make_shared<Asteroid>(x, topBorderHeight_ + 300, direction));
}

void EntityCreator::createHumanoid(const vector<int> &randomNumbers)
{
    const auto direction = randomNumbers[0] % 2;
    const auto x = get<0>(GameEntity::allEntities[0]->getPosition()) + (direction ? 1 : -1) * (randomNumbers[1] % 600);
    EnemyEntity::allEntities.push_back(make_shared<Humanoid>(x, bottomBorderHeight_, direction));
}

void EntityCreator::createFuelTank(const vector<int> &randomNumbers)
{
    const auto direction = randomNumbers[0] % 2;
    const auto x = get<0>(GameEntity::allEntities[0]->getPosition()) + (randomNumbers[1] % 1800) - 900;
    EnemyEntity::allEntities.push_back(make_shared<FuelTank>(x, bottomBorderHeight_, true));
}

entityPosition EntityCreator::enemySpawnPosition(const vector<int> &randomNumbers)
{
    const auto directionX = double{randomNumbers[0] % 2 ? 1.0 : -1.0};
    const auto directionY = double{randomNumbers[1] % 2 ? 1.0 : -1.0};

    const auto playerPosition = GameEntity::allEntities[0]->getPosition();
    const auto minSpawnX = int{400};
    const auto maxSpawnX = int{700};
    const auto minSpawnY = int{100};
    const auto maxSpawnY = int{300};

    auto newX = double{get<0>(playerPosition) + directionX * (minSpawnX + randomNumbers[2] % (maxSpawnX - minSpawnX))};
    auto newY = double{get<1>(playerPosition) + directionY * (minSpawnY + randomNumbers[3] % (maxSpawnY - minSpawnY))};

    if (newY < bottomBorderHeight_ || newY > topBorderHeight_)
    {
        newY = 2 * get<1>(playerPosition) - newY;
    }

    const auto direction = bool{directionX < 0};
    return {newX, newY, direction};
}

vector<int> EntityCreator::newVect(const vector<int> &numbers, int start)
{
    return vector<int>(numbers.begin() + start, numbers.end());
}

EntityCreator::~EntityCreator() {}