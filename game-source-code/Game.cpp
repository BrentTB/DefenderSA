#include "Game.h"

Game::Game() : entityCreator_(700, 50),
               entityManager_(make_shared<EntityManager>(700, 50, 1600)),
               entityDestroyer_(),
               humanoidKidnapping_(entityManager_, 700, 50),
               window_(60, 1600, 900),
               gameWidth_(6400),
               state_(GameState::Start)
{
    srand(time(0));
}

void Game::startGame()
{
    while (state_ != GameState::Exit)
    {
        reset_ = false;
        gameLoop();
    }
}

void Game::findState()
{
    auto input = window_.getKeyboardInput();

    if (!input[UserInput::KeyP] && !input[UserInput::KeyI])
    {
        canPause_ = true;
    }

    if (input[UserInput::KeyEscape])
    {
        state_ = GameState::Exit;
        reset_ = true;
    }
    else if (GameEntity::allEntities[0]->isDestroyed() && state_ != GameState::GameOver)
    {
        state_ = GameState::GameOver;
    }
    else if(state_ == GameState::Start && input[UserInput::KeyI] && canPause_)
    {
        state_ = GameState::Info;
        canPause_ = false;
    }    
    else if(state_ == GameState::Info && input[UserInput::KeyI] && canPause_)
    {
        state_ = GameState::Start;
        canPause_ = false;
    }
    else if ((state_ == GameState::Pause || state_ == GameState::Start) && input[UserInput::KeyP] && canPause_)
    {
        state_ = GameState::Playing;
        Clock::setGameIsPaused(false);
        canPause_ = false;
    }
    else if (state_ == GameState::Playing && input[UserInput::KeyP] && canPause_)
    {
        state_ = GameState::Pause;
        canPause_ = false;
        Clock::setGameIsPaused(true);
    }
    else if (state_ == GameState::GameOver && input[UserInput::KeyEnter])
    {
        reset_ = true;
    }
}

void Game::updateEntites()
{
    if (entityManager_->tryRefillFuel())
        dpc<Player>(GameEntity::allEntities[0])->refillFuel();

    dpc<Player>(GameEntity::allEntities[0])->setUserInput(window_.getKeyboardInput());
    auto fireIndexes = vector<int>{};
    for (auto i = 0; i < GameEntity::allEntities.size(); i++)
    {
        auto entity = GameEntity::allEntities[i];
        entity->wrapPosition(screenPos_+800, gameWidth_);
        auto fire = entity->update(deltaTime_);
        if (fire && entityManager_->onScreen(get<0>(entity->getPosition()), get<1>(entity->getPosition()), screenPos_))
            fireIndexes.push_back(i);
    }
    entityCreator_.createProjectiles(fireIndexes);
}

void Game::generateEntities()
{
    if (entityCreator_.tryLevelUp(numEnemiesDestroyed_))
    {
        level_++;
        dpc<Player>(GameEntity::allEntities[0])->levelUp();
        numEnemiesDestroyed_ = 0;
        entityDestroyer_.removeEntityType(EntityList::Mine);
        window_.levelUp();
    }
    entityCreator_.tryRandomEvents(deltaTime_);
}

void Game::renderScreen()
{
    findScreenPos();
    const auto playerInformation = dpc<Player>(GameEntity::allEntities[0])->getPlayerInformation();
    window_.update(state_, screenPos_);
    window_.display(level_, score_, playerInformation);
}

void Game::removeDestroyedEntities()
{
    auto destroyResult = entityDestroyer_.removeDestroyedEntities();
    numEnemiesDestroyed_ += get<0>(destroyResult);
    score_ += get<1>(destroyResult);
}

void Game::resetGameVariables()
{
    level_ = 1;
    score_ = 0;
    deltaTime_ = 1.0 / 60;
    state_ = GameState::Start;
    canPause_ = true;
    screenPos_ = 0;
    numEnemiesDestroyed_ = 0;
    entityCreator_.reset();
    Clock::reset();
}

void Game::findScreenPos()
{
    if (state_ != GameState::Playing)
        return;

    const auto playerX = get<0>(GameEntity::allEntities[0]->getPosition());
    const auto playerDirection = get<2>(GameEntity::allEntities[0]->getPosition());
    const auto screenWidth = double{1600};
    const auto playerEdgeDistance = screenWidth * 2.0 / 3;
    auto desiredScreenPos = double{0};

    if (!playerDirection)
    {
        if (playerX < screenPos_ + playerEdgeDistance)
        {
            desiredScreenPos = playerX - playerEdgeDistance;
        }
        else
        {
            desiredScreenPos = playerX + (playerEdgeDistance / 2 - screenWidth);
        }
    }
    else
    {
        if (playerX > screenWidth + screenPos_ - playerEdgeDistance)
        {
            desiredScreenPos = playerX + (playerEdgeDistance - screenWidth);
        }
        else
        {
            desiredScreenPos = playerX - playerEdgeDistance / 2;
        }
    }

    const auto screenMoveFactor = double{15};
    const auto maxMove = double{800};

    desiredScreenPos = ((1 - screenMoveFactor * deltaTime_) * screenPos_ + screenMoveFactor * deltaTime_ * desiredScreenPos);

    if (desiredScreenPos > screenPos_)
    {
        screenPos_ += min(desiredScreenPos - screenPos_, maxMove * deltaTime_);
    }
    else
    {
        screenPos_ -= min(screenPos_ - desiredScreenPos, maxMove * deltaTime_);
    }
}
void Game::gameLoop()
{
    resetGameVariables();
    while (!reset_)
    {
        deltaTime_ = Clock::getDeltaTime();
        findState();
        if (state_ == GameState::Playing)
        {
            entityManager_->checkOffScreenProjectiles(screenPos_);
            humanoidKidnapping_.checkKidnapping(screenPos_);
            entityManager_->checkEntityCollisions();
            updateEntites();
            generateEntities();
            removeDestroyedEntities();
        }
        renderScreen();
    }
    entityDestroyer_.removeAllEntities();
}

Game::~Game() {}
