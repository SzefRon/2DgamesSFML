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

    maxG = 2.0f * maxJumpHeight * (speed * speed) / (maxJumpLength * maxJumpLength);
    maxVY0 = maxG * maxJumpLength / (speed);
    minG = 2.0f * minJumpHeight * (speed * speed) / (minJumpLength * minJumpLength);
    minVY0 = minG * maxJumpLength / (speed);
    g = maxG;

    jumps = availableJumps;

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

void Player::manageMovement(InputHandler *inputHandler, sf::Time dt)
{
    if (onGround) {
        jumps = availableJumps;
        g = maxG;
    }
    else if (jumps == availableJumps)
        jumps--;

    float dtSec = dt.asSeconds();
    vx = vx * powf(slipperiness, dtSec * 1000.0f);

    if (inputHandler->keyboardPresses[directionKeys[Up]] && jumps > 0) {
        vy = -maxVY0;
        g = maxG;
        jumps--;
    }
    if (inputHandler->keyboardInputs[directionKeys[Right]]) {
        vx = speed;
    }
    if (inputHandler->keyboardInputs[directionKeys[Left]]) {
        vx = -speed;
    }
    if (inputHandler->keyboardReleases[directionKeys[Up]]) {
        g = minG;
        vy = Maths::max(vy, -minVY0);
    }

    if (vy >= 0.0f) g = maxG;

    x += (vx) * dtSec;

    y += (vy) * dtSec + 0.5f * g * dtSec * dtSec;
    vy += g * dtSec;

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

void Player::resetDownwardVelocity()
{
    vy = 0.0f;
}

void Player::setPosition(sf::Vector2f vec)
{
    x = vec.x;
    y = vec.y;

    sprite->sprite->setPosition(x, y);
}

void Player::setVelocity(sf::Vector2f vec)
{
    vx = vec.x;
    vy = vec.y;
}

sf::Vector2f Player::getPosition()
{
    return sf::Vector2f(x, y);
}

sf::Vector2f Player::getVelocity()
{
    return sf::Vector2f(vx, vy);
}
