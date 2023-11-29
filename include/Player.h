#pragma once

#include <SFML/Graphics.hpp>
#include <InputHandler.h>
#include <map>

class Player
{
private:
    float x, y, speed = 1.0f, slipperiness = 0.99f;
    float vx = 0.f, vy = 0.f;
    sf::Keyboard::Scan::Scancode directionKeys[4];
public:
    sf::Sprite *sprite;
    Player(ControlType controlType, sf::Texture &texture, float startX, float startY);
    ~Player();

    void move(std::map<sf::Keyboard::Scan::Scancode, bool> &keyboardInputs, sf::Time dt);
    sf::Vector2f getPos();
};