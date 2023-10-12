#ifndef KEYBOARDINPUT
#define KEYBOARDINPUT

/**
 * @file KeyboardInput.h
 * @brief File that holds the keyboard input class
 */
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include "UserInput.h"

using namespace std;

/**
 * @class KeyboardInput
 * @brief Class that managed and defines the keys that are pressed by the user. 
 * 
 * @see UserInput 
 */
class KeyboardInput
{
public:
    /**
     * @brief Construct a new Keyboard Input object
     */
    KeyboardInput();

    /**
     * @brief Get the Keyboard Input object
     * 
     * @return map<UserInput, bool>& - Map to set if the key is pressed or not
     */
    map<UserInput, bool> &getKeyboardInput();    

    /**
     * @brief Set the Keyboard Input object
     * This populates the userInput_ vector. 
     * @param event Causes a change in the game once a key is pressed
     */
    void setKeyboardInput(const sf::Event &event); 

    /**
     * @brief Destroy the Keyboard Input object
     */
    ~KeyboardInput();

private:
    map<UserInput, bool> keyboardInput_;              /*which keys the user is currently pressing*/ 
    map<sf::Keyboard::Key, UserInput> inputMatching_; /*maps the keyboard input to a UserInput enum object*/ 
};

#endif