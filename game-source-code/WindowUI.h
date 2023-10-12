#ifndef WINDOWUI
#define WINDOWUI

/**
 * @file WindowUI.h
 * @brief File that holds all the UI implementation of the game
 */
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include "GameState.h"
#include "EntityList.h"
#include "GameEntity.h"
#include "KeyboardInput.h"
#include "FileManager.h"
#include "UserInput.h"
#include "ScoreManager.h"

using namespace std;

/**
 * @class WindowUI
 * @brief Class manages the UI implementation of the game
 *
 */
class WindowUI
{
public:
    /**
     * @brief Construct a new Window UI object
     * make the sf::renderwindow, call file loader and inputSetUp
     * @param FPS - Frames per Second
     * @param width - Width of the screen
     * @param height - Height of the screen
     */
    WindowUI(const double &FPS, const double &width, const double &height);

    /**
     * @brief Displays the level up animation
     */
    void levelUp();

    /**
     * @brief Calls storeKeyboardInput and any other window functions that should refresh
     *
     * @param state - The state in which the game is in
     * @param screenPos - The position of the visible screen
     */
    void update(const GameState &state, const double &screenPos);

    /**
     * @brief Get the Keyboard Input object
     * populates the userInput_ vector
     * @return map<UserInput, bool>&
     */
    map<UserInput, bool> &getKeyboardInput();

    /**
     * @brief  Calls one of the private display functions based on state_
     *
     * @param level - Level the player is on
     * @param score - Players score
     * @param playerInformation - <shieldCound, fuelLevel>
     */
    void display(const int &level, const int &score, const tuple<int, double> &playerInformation);

    /**
     * @brief Destroy the Window UI object
     */
    ~WindowUI();

private:
    /**
     * @brief Displays the Splash, Pause or end screen
     *
     * @param screenTexture - Splash, Pause or End
     */
    void displayScreen(sf::Texture screenTexture);

    /**
     * @brief Displays all objects, called when in a normal game
     *
     * @param level - Players level
     * @param shieldCount - Number of shields the player has left
     * @param fuelPercentage - Amount of fuel the player has left
     */
    void displayPlaying(const int &level, const int &shieldCount, const double &fuelPercentage);

    /**
     * @brief Implements the scrolling background which moves with the player
     */
    void scrollingBackground();

    /**
     * @brief Displays the number of shields the player has left
     *
     * @param shieldCount - Number of shields the player has left
     * @return * void
     */
    void displayShieldCount(const int &shieldCount);

    /**
     * @brief Displays the amount of fuel the player has left
     *
     * @param fuelPercentage - The percentage of fuel player has left
     */
    void displayFuelBar(const double &fuelPercentage);

    /**
     * @brief Displays the players score
     */
    void displayScore();

    /**
     * @brief Displays the level the player is on.
     *
     * @param level - The current level the player is on
     */
    void displayLevel(const int &level);

    /**
     * @brief Displays the game over screen with thhe players score
     */
    void displayGameOver();

    /**
     * @brief Displays all entities on screen
     */
    void displayEntities();

    /**
     * @brief Displays the entities on the minimap
     */
    void displayMinimapEntities();

    /**
     * @brief Displays the minimap on the top of the screen
     */
    void displayMiniMap();
    

    /**
     * @brief Loads in all the textures and fonts from file loader
     */
    void loadTexturesAndFonts();

    // Textures
    sf::Font mainFont_;                          /*The main font used*/
    sf::Texture loseTexture_;                    /*The textere when player loses*/
    sf::Texture startScreenTexture_;             /*The start screen texture*/
    sf::Texture pauseScreenTexture_;             /*The pause screen texture*/
    sf::Texture infoScreenTexture_;              /*The information screen texture*/
    sf::Texture backgroundTexture_;              /*The background texture*/
    sf::Texture borderTexture_;                  /*The minimap screen border texture*/
    map<EntityList, sf::Texture> entityTexture_; /*The dummy texture for each entity*/

    KeyboardInput keyboardInput_; /*Calls the keyboard input object*/
    FileManager fileManager_;     /*Calls the file manager object*/
    ScoreManager scoreManager_;   /*Calls the score manager object*/

    sf::RenderWindow window_; /*Renders the game window*/
    GameState state_;         /*Defines the gamestate enum*/

    double screenPos_;       /*The variable that defines the screen position*/
    float levelUpShowTimer_; /*The timer used for the level up display*/

    int score_; /*The players score*/
};

#endif