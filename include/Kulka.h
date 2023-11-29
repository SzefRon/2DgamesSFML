#pragma once

#include <SFML/Graphics.hpp>

class Kulka
{
public:
    float x, y;
    float vx, vy;
    sf::Sprite *sprite;
    Kulka(sf::Texture &texture, float startX, float startY, float vx, float vy);

    void setPos(float newX, float newY);
    void move(float dx, float dy);
};