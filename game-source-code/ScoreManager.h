#ifndef SCOREMANAGER
#define SCOREMANAGER

/**
 * @file ScoreManager.h
 * @brief File that holds all the definition of the ScoreManager
 */
#include <vector>
#include <algorithm>
#include "FileManager.h"

#include <iostream>

using namespace std;

/**
 * @class ScoreManager
 * @brief The class that holds all the functionality for the score manager
 *
 */
class ScoreManager
{
public:
    /**
     * @brief Construct a new Score Manager object
     */
    ScoreManager();

    /**
     * @brief Function that get the bestScore from the list of scores
     *
     * @return int -best score
     */
    int bestScore();

    /**
     * @brief Get the Leaderboard
     * adds the current score to the leaderboard
     *
     * @return string - the string that holds all the scores
     */
    string getLeaderboard();

    /**
     * @brief This saves the score to the text file
     */
    void saveScore();

    /**
     * @brief This adds the score to the vector when the game ends
     *
     * @param score - Score achieved
     */
    void gameOver(const int &score); // adds the score to the vector

    /**
     * @brief Destroy the Score Manager object
     */
    ~ScoreManager();

private:
    /**
     * @brief Sorts thhe scores into decending order
     */
    void sortScore();

    FileManager fileManager_; /*Calls the fileManager object to access the text file*/
    vector<int> allScores_;   /*Vector that holds all scores*/
};

#endif