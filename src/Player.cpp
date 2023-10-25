#include "Player.h"

#include <iostream>
#include <math.h>

Player::Player(sf::Texture &texture, float startX, float startY)
{
    sprite = new sf::Sprite(texture);
    x = startX;
    y = startY;
    sprite->setPosition(x, y);
    sf::Vector2u textureSize = texture.getSize();
    sprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    sprite->setScale(1.0f, 1.0f);
}

Player::~Player()
{
    delete sprite;
}

void Player::move(std::map<sf::Keyboard::Scan::Scancode, bool> &keyboardInputs, sf::Time dt)
{
    vx = vx * powf(slipperiness, dt.asMilliseconds());
    vy = vy * powf(slipperiness, dt.asMilliseconds());

    if (keyboardInputs[sf::Keyboard::Scan::Scancode::Up]) {
        vy = -1.0f;
    }
    if (keyboardInputs[sf::Keyboard::Scan::Scancode::Down]) {
        vy = 1.0f;
    }
    if (keyboardInputs[sf::Keyboard::Scan::Scancode::Right]) {
        vx = 1.0f;
    }
    if (keyboardInputs[sf::Keyboard::Scan::Scancode::Left]) {
        vx = -1.0f;
    }

    float vLength = std::sqrtf(vx * vx + vy * vy);

    if (vLength > 1.0f) {
        vx = vx / vLength;
        vy = vy / vLength;
    }

    x += (vx) * speed * dt.asMilliseconds();
    y += (vy) * speed * dt.asMilliseconds();

    sprite->setPosition(x, y);
}

sf::Vector2f Player::getPos()
{
    return sf::Vector2f(x, y);
}
