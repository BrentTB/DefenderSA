#include "WindowUI.h"

WindowUI::WindowUI(const double &FPS, const double &width, const double &height) : keyboardInput_(),
                                                                                   fileManager_(),
                                                                                   scoreManager_(),
                                                                                   window_(sf::VideoMode(width, height), "Destroyer: SA", sf::Style::Titlebar | sf::Style::Close),
                                                                                   state_(GameState::Start),
                                                                                   levelUpShowTimer_(-1),
                                                                                   screenPos_(0)
{
    window_.setVerticalSyncEnabled(true);
    window_.setKeyRepeatEnabled(false);
    window_.setFramerateLimit(FPS);
    window_.setVisible(true);
    loadTexturesAndFonts();
}

void WindowUI::levelUp()
{
    levelUpShowTimer_ = Clock::getGameTime() + 2;
}

void WindowUI::update(const GameState &state, const double &screenPos)
{
    screenPos_ = screenPos;
    if (state == GameState::GameOver && state != state_)
    {
        scoreManager_.gameOver(score_);
        screenPos_ = 0;
    }

    state_ = state;
    auto event = sf::Event{};
    while (window_.pollEvent(event))
    {
        keyboardInput_.setKeyboardInput(event);
    }
    if (state_ == GameState::Exit)
    {
        scoreManager_.saveScore();
        window_.close();
    }
}

map<UserInput, bool> &WindowUI::getKeyboardInput()
{
    return keyboardInput_.getKeyboardInput();
}

void WindowUI::display(const int &level, const int &score, const tuple<int, double> &playerInformation)
{
    score_ = score;
    window_.clear(sf::Color(0, 0, 0));
    switch (state_)
    {
    case GameState::Start:
        displayScreen(startScreenTexture_);
        break;
    case GameState::Pause:
        displayScreen(pauseScreenTexture_);
        break;
    case GameState::Info:
        displayScreen(infoScreenTexture_);
        break;
    case GameState::GameOver:
        displayGameOver();
        break;
    case GameState::Playing:
        displayPlaying(level, get<0>(playerInformation), get<1>(playerInformation));
        break;
    case GameState::Exit:
        break;
    default:
        assert(false);
        break;
    }
    window_.display();
}

void WindowUI::displayGameOver()
{
    displayScreen(loseTexture_);

    stringstream score_ss;
    score_ss << "Final Score: " << score_ << endl;

    auto displaytext = sf::Text{};
    displaytext.setFont(mainFont_);
    displaytext.setCharacterSize(60);
    displaytext.setFillColor(sf::Color::Black);

    displaytext.setPosition(window_.getSize().x - 1150, 300.0);
    displaytext.setString(score_ss.str());
    window_.draw(displaytext);
}

void WindowUI::displayScreen(sf::Texture screenTexture)
{
    auto screen = sf::Sprite{};
    screen.setTexture(screenTexture);
    window_.draw(screen);
}

void WindowUI::displayPlaying(const int &level, const int &shieldCount, const double &fuelPercentage)
{
    scrollingBackground();
    displayScore();
    displayLevel(level);
    displayEntities();
    displayShieldCount(shieldCount);
    displayFuelBar(fuelPercentage);
    displayMiniMap();
}

void WindowUI::scrollingBackground()
{
    auto backgroundSprite = sf::Sprite{};
    backgroundSprite.setTexture(backgroundTexture_);

    const auto width = float{backgroundSprite.getGlobalBounds().width};
    const auto height = window_.getSize().y - float{backgroundSprite.getGlobalBounds().height};
    const auto pos = fmod(screenPos_ + window_.getSize().x / 2, width);
    for (auto i = -3; i < 4; i++)
    {
        backgroundSprite.setPosition(i * width - pos, height);
        window_.draw(backgroundSprite);
    }
}

void WindowUI::displayEntities()
{
    for (auto entity : GameEntity::allEntities)
    {
        auto sprite = sf::Sprite{};
        const auto position = entity->getPosition();
        sprite.setTexture(entityTexture_[entity->getType()]);
        sprite.setOrigin(entityTexture_[entity->getType()].getSize().x / 2, entityTexture_[entity->getType()].getSize().y / 2);
        sprite.rotate(-entity->getTiltAngle() * 180 / M_PI);
        sprite.setPosition(get<0>(position) - screenPos_, window_.getSize().y - get<1>(position));
        if (!get<2>(position))
            sprite.setScale(-1.f, 1.f);
        window_.draw(sprite);
    }
}

void WindowUI::displayMinimapEntities()
{
    for (auto entity : GameEntity::allEntities)
    {
        if (entity->getType() == EntityList::LanderLaser || entity->getType() == EntityList::PlayerLaser || entity->getType() == EntityList::Mine || entity->getType() == EntityList::Asteroid)
            continue;
        auto sprite = sf::Sprite{};
        const auto position = entity->getPosition();
        sprite.setTexture(entityTexture_[entity->getType()]);
        sprite.setOrigin(entityTexture_[entity->getType()].getSize().x / 2, entityTexture_[entity->getType()].getSize().y / 2);
        sprite.rotate(-entity->getTiltAngle() * 180 / M_PI);
        sprite.setPosition(get<0>(position) - screenPos_, window_.getSize().y - get<1>(position));
        if (!get<2>(position))
            sprite.setScale(-1.f, 1.f);
        window_.draw(sprite);
    }
}

void WindowUI::displayMiniMap()
{
    auto minimap = sf::View(sf::Vector2f(window_.getSize().x / 2, window_.getSize().y / 2), sf::Vector2f(window_.getSize().x * 4, window_.getSize().y));
    minimap.setViewport(sf::FloatRect(0.25f, 0, 0.5f, 180.0f / window_.getSize().y));
    window_.setView(minimap);

    auto minimapBackground = sf::RectangleShape(sf::Vector2f(window_.getSize().x * 4.0f, window_.getSize().y));
    minimapBackground.setOrigin(minimapBackground.getSize().x / 2, minimapBackground.getSize().y / 2);
    minimapBackground.setPosition(window_.getSize().x / 2, window_.getSize().y / 2);
    minimapBackground.setFillColor(sf::Color(0, 0, 0, 150));
    window_.draw(minimapBackground);
    
    scrollingBackground();
    displayMinimapEntities();

    auto minimapBorder = sf::Sprite{};
    minimapBorder.setTexture(borderTexture_);
    minimapBorder.setOrigin((get<0>(GameEntity::allEntities[0]->getPosition()) - screenPos_) / window_.getSize().x * minimapBorder.getGlobalBounds().width, 0);
    minimapBorder.setPosition(get<0>(GameEntity::allEntities[0]->getPosition()) - screenPos_, 0);
    window_.draw(minimapBorder);

    window_.setView(window_.getDefaultView());
}

void WindowUI::displayShieldCount(const int &shieldCount)
{
    auto shieldCountText = sf::Text{};
    shieldCountText.setFont(mainFont_);
    shieldCountText.setCharacterSize(25);
    shieldCountText.setPosition(10.0, 10.0);
    shieldCountText.setFillColor(sf::Color::White);
    shieldCountText.setString("Shield Count:");
    window_.draw(shieldCountText);

    for (int i = 0; i < shieldCount; i++)
    {
        sf::Sprite PlayerShield1;
        PlayerShield1.setTexture(entityTexture_[EntityList::PlayerShield]);
        PlayerShield1.setScale(0.8f, 0.8f);
        PlayerShield1.setPosition(10 + (i * 100), 0 + PlayerShield1.getGlobalBounds().height);
        window_.draw(PlayerShield1);
    }
}

void WindowUI::displayFuelBar(const double &fuelPercentage)
{
    auto fuelBar = sf::RectangleShape{};

    fuelBar.setSize(sf::Vector2f(250.f, 20.f));
    fuelBar.setFillColor(sf::Color(175, 5, 5));
    fuelBar.setPosition(100.f, 145.f);

    auto fuelBarBack = fuelBar;
    fuelBarBack.setFillColor(sf::Color(45, 10, 10, 200));
    fuelBarBack.setOutlineColor(sf::Color::White);
    fuelBarBack.setOutlineThickness(3.f);

    fuelBar.setSize(sf::Vector2f(250.f * (fuelPercentage / 100), fuelBar.getSize().y));

    auto FuelTank = sf::Sprite{};
    FuelTank.setTexture(entityTexture_[EntityList::FuelTank]);
    FuelTank.setPosition(8.f, 100.f);

    window_.draw(fuelBarBack);
    window_.draw(fuelBar);
    window_.draw(FuelTank);
}

void WindowUI::displayScore()
{
    auto displaytext = sf::Text{};
    displaytext.setFont(mainFont_);
    displaytext.setCharacterSize(25);
    displaytext.setFillColor(sf::Color::White);

    stringstream highscore_ss, score_ss;
    highscore_ss << "High Score: " << scoreManager_.bestScore() << endl;
    score_ss << "Score: " << score_ << endl;

    displaytext.setPosition(window_.getSize().x - 385, 10.0);
    displaytext.setString(highscore_ss.str());
    window_.draw(displaytext);

    displaytext.setPosition(window_.getSize().x - 280, 40.0);
    displaytext.setString(score_ss.str());
    window_.draw(displaytext);
}

void WindowUI::displayLevel(const int &level)
{
    auto displaytext = sf::Text{};
    displaytext.setFont(mainFont_);
    displaytext.setCharacterSize(25);
    displaytext.setFillColor(sf::Color::White);

    stringstream level_ss, levelUp_ss;
    level_ss << "Level: " << level << endl;
    levelUp_ss << "Level Up " << endl;

    displaytext.setPosition(window_.getSize().x - 280, 70.0);
    displaytext.setString(level_ss.str());
    window_.draw(displaytext);

    if (levelUpShowTimer_ > Clock::getGameTime())
    {
        displaytext.setScale(3, 3);
        displaytext.setOrigin(displaytext.getLocalBounds().width / 2, displaytext.getLocalBounds().height / 2);
        auto factor = (200 + window_.getSize().y) / 2;
        displaytext.setPosition(window_.getSize().x / 2, window_.getSize().y + 100 - factor * (levelUpShowTimer_ - Clock::getGameTime()));
        displaytext.setString(levelUp_ss.str());
        window_.draw(displaytext);
    }
}

void WindowUI::loadTexturesAndFonts()
{
    mainFont_ = fileManager_.getFont("resources/Joystix monospace.otf");
    startScreenTexture_ = fileManager_.getTexture("resources/StartScreen.png");
    pauseScreenTexture_ = fileManager_.getTexture("resources/PauseScreen.png");
    infoScreenTexture_ = fileManager_.getTexture("resources/InfoScreen.png");
    loseTexture_ = fileManager_.getTexture("resources/GameOver.png");
    backgroundTexture_ = fileManager_.getTexture("resources/BackgroundScreen.png");
    borderTexture_ = fileManager_.getTexture("resources/BorderImage.png");
    entityTexture_[EntityList::Player] = fileManager_.getTexture("resources/PlayerCar.png");
    entityTexture_[EntityList::PlayerShield] = fileManager_.getTexture("resources/PlayerCarShield.png");
    entityTexture_[EntityList::PlayerLaser] = fileManager_.getTexture("resources/GreenLaser.png");
    entityTexture_[EntityList::Lander] = fileManager_.getTexture("resources/LanderTaxi.png");
    entityTexture_[EntityList::LanderLaser] = fileManager_.getTexture("resources/RedLaser.png");
    entityTexture_[EntityList::Bomber] = fileManager_.getTexture("resources/Eishkom.png");
    entityTexture_[EntityList::Mine] = fileManager_.getTexture("resources/Pothole.png");
    entityTexture_[EntityList::Asteroid] = fileManager_.getTexture("resources/Asteroid.png");
    entityTexture_[EntityList::Humanoid] = fileManager_.getTexture("resources/Humanoid.png");
    entityTexture_[EntityList::FuelTank] = fileManager_.getTexture("resources/FuelTank.png");
}

WindowUI::~WindowUI() {}