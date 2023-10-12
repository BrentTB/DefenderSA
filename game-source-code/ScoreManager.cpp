#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
    const auto scoreString = fileManager_.getLinesFromFile("resources/scores.txt");
    std::transform(scoreString.begin(), scoreString.end(), std::back_inserter(allScores_),
                   [](const string &str)
                   { return stoi(str); });
    auto all = string{""};
    for (auto line : allScores_)
    {
        all += to_string(line) + "\n";
    }
    sortScore();
}

int ScoreManager::bestScore()
{
    return allScores_[0];
}

string ScoreManager::getLeaderboard()
{
    auto leaderboard = string{};
    for (auto line : allScores_)
    {
        leaderboard += to_string(line) + "\n";
    }
    return leaderboard;
}

void ScoreManager::saveScore()
{
    fileManager_.setFile("resources/scores.txt", getLeaderboard());
}

void ScoreManager::gameOver(const int &score)
{
    allScores_.push_back(score);
    sortScore();
}

void ScoreManager::sortScore()
{
    sort(allScores_.begin(), allScores_.end(), greater<int>());
}

ScoreManager::~ScoreManager(){};