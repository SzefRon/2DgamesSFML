#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class Player
{
private:
    float x, y, speed = 1.0f, slipperiness = 0.99f;
public:
    sf::Sprite *sprite;
    float vx = 0.f, vy = 0.f;

    Player(sf::Texture &texture, float startX, float startY);
    ~Player();
    void move(std::map<sf::Keyboard::Scan::Scancode, bool> &keyboardInputs, sf::Time dt);
};