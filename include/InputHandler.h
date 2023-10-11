#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

class InputHandler
{
private:
    sf::RenderWindow *window;
public:
    InputHandler(sf::RenderWindow *window);
    void handleEvents();
    std::map<sf::Keyboard::Scan::Scancode, bool> keyboardInputs;
    std::map<sf::Mouse::Button, bool> mouseInputs;
    std::pair<unsigned int, unsigned int> mousePos;
};