#include "Player.h"

#include <iostream>
#include <math.h>

Player::Player(ControlType controlType, sf::Texture &texture, float startX, float startY, CollisionType collisionType)
{
    sprite = new Sprite(new sf::Sprite(texture), collisionType);
    x = startX;
    y = startY;
    sprite->sprite->setPosition(x, y);
    sf::Vector2u textureSize = texture.getSize();
    sprite->sprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    sprite->sprite->setScale(1.0f, 1.0f);

    switch (controlType)
    {
    case WASD:
        directionKeys[Up] = sf::Keyboard::Scan::Scancode::W;
        directionKeys[Down] = sf::Keyboard::Scan::Scancode::S;
        directionKeys[Left] = sf::Keyboard::Scan::Scancode::A;
        directionKeys[Right] = sf::Keyboard::Scan::Scancode::D;
        break;
    case Arrows:
        directionKeys[Up] = sf::Keyboard::Scan::Scancode::Up;
        directionKeys[Down] = sf::Keyboard::Scan::Scancode::Down;
        directionKeys[Left] = sf::Keyboard::Scan::Scancode::Left;
        directionKeys[Right] = sf::Keyboard::Scan::Scancode::Right;
        break;
    }
}

Player::~Player()
{
    delete sprite;
}

void Player::manageMovement(std::map<sf::Keyboard::Scan::Scancode, bool> &keyboardInputs, sf::Time dt)
{
    vx = vx * powf(slipperiness, dt.asMilliseconds());
    vy = vy * powf(slipperiness, dt.asMilliseconds());

    if (keyboardInputs[directionKeys[Up]]) {
        vy = -1.0f;
    }
    if (keyboardInputs[directionKeys[Down]]) {
        vy = 1.0f;
    }
    if (keyboardInputs[directionKeys[Right]]) {
        vx = 1.0f;
    }
    if (keyboardInputs[directionKeys[Left]]) {
        vx = -1.0f;
    }

    float vLength = std::sqrtf(vx * vx + vy * vy);

    if (vLength > 1.0f) {
        vx = vx / vLength;
        vy = vy / vLength;
    }

    x += (vx) * speed * dt.asMilliseconds();
    y += (vy) * speed * dt.asMilliseconds();

    sprite->sprite->setPosition(x, y);
}

void Player::move(sf::Vector2f vec)
{
    x += vec.x;
    y += vec.y;

    sprite->sprite->setPosition(x, y);
}

void Player::resetVelocity()
{
    vx = 0.0f;
    vy = 0.0f;
}

void Player::setPosition(sf::Vector2f vec)
{
    x = vec.x;
    y = vec.y;

    sprite->sprite->setPosition(x, y);
}

sf::Vector2f Player::getPosition()
{
    return sf::Vector2f(x, y);
}
