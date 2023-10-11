#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class MousePlayer
{
private:
    float x, y, speed = 1.0f, slipperiness = 0.995f;
public:
    sf::Sprite *sprite;
    float vx = 0.f, vy = 0.f;

    MousePlayer(sf::Texture &texture, float startX, float startY);
    ~MousePlayer();
    void move(std::map<sf::Mouse::Button, bool> &mouseInputs, std::pair<unsigned int, unsigned int> &mousePos, sf::Time dt);
};