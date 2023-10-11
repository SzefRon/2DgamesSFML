#include "MousePlayer.h"

#include <iostream>

MousePlayer::MousePlayer(sf::Texture &texture, float startX, float startY)
{
    sprite = new sf::Sprite(texture);
    x = startX;
    y = startY;
    sprite->setPosition(x, y);
    sf::Vector2u textureSize = texture.getSize();
    sprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    sprite->setScale(1.0f, 1.0f);
}

MousePlayer::~MousePlayer()
{
    delete sprite;
}

void MousePlayer::move(std::map<sf::Mouse::Button, bool> &mouseInputs, std::pair<unsigned int, unsigned int> &mousePos, sf::Time dt)
{
    vx = vx * pow(slipperiness, dt.asMilliseconds());
    vy = vy * pow(slipperiness, dt.asMilliseconds());

    float dx = mousePos.first - x;
    float dy = mousePos.second - y;
    float vLength = std::sqrtf(dx * dx + dy * dy);

    if (mouseInputs[sf::Mouse::Button::Left]) {
        if (vLength > 0.0f) {
            float multiplier = (50.0f / (-vLength - 50.0f)) + 1.0f;
            vx = (dx / vLength) * multiplier;
            vy = (dy / vLength) * multiplier;
        }
    }

    x += vx * speed * dt.asMilliseconds();
    y += vy * speed * dt.asMilliseconds();

    sprite->setPosition(x, y);
}
