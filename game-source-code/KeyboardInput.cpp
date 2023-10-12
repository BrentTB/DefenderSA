#include "KeyboardInput.h"

KeyboardInput::KeyboardInput()
{
    keyboardInput_[UserInput::KeyEnter] = false;
    keyboardInput_[UserInput::KeyEscape] = false;
    keyboardInput_[UserInput::KeySpace] = false;
    keyboardInput_[UserInput::KeyP] = false;
    keyboardInput_[UserInput::KeyW] = false;
    keyboardInput_[UserInput::KeyA] = false;
    keyboardInput_[UserInput::KeyS] = false;
    keyboardInput_[UserInput::KeyD] = false;
    keyboardInput_[UserInput::KeyI] = false;

    inputMatching_[sf::Keyboard::Enter] = UserInput::KeyEnter;
    inputMatching_[sf::Keyboard::Escape] = UserInput::KeyEscape;
    inputMatching_[sf::Keyboard::Space] = UserInput::KeySpace;
    inputMatching_[sf::Keyboard::P] = UserInput::KeyP;
    inputMatching_[sf::Keyboard::W] = UserInput::KeyW;
    inputMatching_[sf::Keyboard::Up] = UserInput::KeyW;
    inputMatching_[sf::Keyboard::A] = UserInput::KeyA;
    inputMatching_[sf::Keyboard::Left] = UserInput::KeyA;
    inputMatching_[sf::Keyboard::S] = UserInput::KeyS;
    inputMatching_[sf::Keyboard::Down] = UserInput::KeyS;
    inputMatching_[sf::Keyboard::D] = UserInput::KeyD;
    inputMatching_[sf::Keyboard::Right] = UserInput::KeyD;
    inputMatching_[sf::Keyboard::I] = UserInput::KeyI;
}

map<UserInput, bool> &KeyboardInput::getKeyboardInput()
{
    return keyboardInput_;
}

void KeyboardInput::setKeyboardInput(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
    {
        if (inputMatching_.count(event.key.code) > 0)
        {
            keyboardInput_[inputMatching_[event.key.code]] = event.type == sf::Event::KeyPressed;
        }
    }
    else if (event.type == sf::Event::Closed)
    {
        keyboardInput_[UserInput::KeyEscape] = true;
    }
}
KeyboardInput::~KeyboardInput() {}