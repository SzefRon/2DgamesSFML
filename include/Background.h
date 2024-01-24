#pragma once

#include <deque>
#include <SFML/Graphics.hpp>
#include <iostream>

class Background
{
private:
    float speed, xOffset, yPos;
    int count;
public:
    std::deque<sf::Sprite *> sprites;
    Background(float speed, float xOffset, float yPos, int count, sf::Sprite *sprite);
    void update(sf::Vector2f cameraPos);
};