#include "Kulka.h"

Kulka::Kulka(sf::Texture &texture, float startX, float startY, float vx, float vy)
    : x(startX), y(startY), vx(vx), vy(vy)
{
    sprite = new sf::Sprite(texture);
    sprite->setPosition(startX, startY);
    sf::Vector2u textureSize = texture.getSize();
    sprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    sprite->setScale(1.0f, 1.0f);
}

void Kulka::setPos(float newX, float newY)
{
    x = newX;
    y = newY;
    sprite->setPosition(sf::Vector2f(x, y));
}

void Kulka::move(float dx, float dy)
{
    x += dx;
    y += dy;
    sprite->move(sf::Vector2f(dx, dy));
}
