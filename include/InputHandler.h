#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

enum ControlType
{
    Arrows,
    WASD
};

enum Direction
{
    Up = 0,
    Left = 1,
    Down = 2,
    Right = 3
};

class InputHandler
{
private:
    sf::RenderWindow *window;
public:
    InputHandler(sf::RenderWindow *window);
    void handleEvents();
    std::map<sf::Keyboard::Scan::Scancode, bool> keyboardInputs;
    std::map<sf::Keyboard::Scan::Scancode, bool> keyboardPresses;
    std::map<sf::Keyboard::Scan::Scancode, bool> keyboardReleases;
    std::map<sf::Mouse::Button, bool> mouseInputs;
    std::pair<unsigned int, unsigned int> mousePos;
};