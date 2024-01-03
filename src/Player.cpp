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
    float dtSec = dt.asSeconds();
    vx = vx * powf(slipperiness, dtSec * 1000.0f);

    if (keyboardInputs[directionKeys[Up]]) {
        vy = -speed * 10.0f;
    }
    if (keyboardInputs[directionKeys[Down]]) {
        vy = speed;
    }
    if (keyboardInputs[directionKeys[Right]]) {
        vx = speed;
    }
    if (keyboardInputs[directionKeys[Left]]) {
        vx = -speed;
    }

    x += (vx) * speed * dtSec;

    float gravity = 64.0f * 15.0f;
    y += (vy) * dtSec + 0.5f * gravity * dtSec * dtSec;
    vy += gravity * dtSec;

    std::cout << vy << '\n';

    sprite->sprite->setPosition(x, y);

    onGround = false;
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

void Player::resetGravity()
{
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
