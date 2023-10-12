#include "GameEntity.h"

GameEntity::GameEntity(const double &x, const double &y, const bool &direction) : x_(x),
                                                                                  y_(y),
                                                                                  direction_(direction),
                                                                                  angle_(0),
                                                                                  isDestroyed_(false),
                                                                                  topBorder_(700),
                                                                                  bottomBorder_(50)
{
}

vector<shared_ptr<GameEntity>> GameEntity::allEntities; 

entityPosition GameEntity::getPosition()
{
    return {x_, y_, direction_};
}

double GameEntity::getTiltAngle()
{
    return 0;
}

entitySize GameEntity::getSize()
{
    return {width_, height_};
}

int GameEntity::getDefeatScore()
{
    return defeatScore_;
}

EntityList GameEntity::getType()
{
    return type_;
}

void GameEntity::destroy()
{
    isDestroyed_ = true;
}

bool GameEntity::isDestroyed()
{
    return isDestroyed_;
}

void GameEntity::wrapPosition(const double &centreX, const double &gameWidth)
{
    while (x_ > centreX + gameWidth / 2)
        x_ -= gameWidth;
    while (x_ < centreX - gameWidth / 2)
        x_ += gameWidth;
}

GameEntity::~GameEntity() {}