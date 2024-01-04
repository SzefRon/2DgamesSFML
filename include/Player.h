#pragma once

#include <SFML/Graphics.hpp>
#include <InputHandler.h>
#include <map>

#include "Sprite.h"
#include "Maths.h"

class Player
{
private:
    float x, y, speed = 20.0f, slipperiness = 0.99f;
    float maxJumpHeight = 128.0f * 3.0f, maxJumpTime = 1.0f;
    float minJumpHeight = 128.0f * 1.0f, minJumpTime = 0.5f;
    int jumps = 0, availableJumps = 3;
    float g = 0.0f;
    float maxG = 0.0f, maxVY0 = 0.0f;
    float minG = 0.0f, minVY0 = 0.0f;
    float vx = 0.0f, vy = 0.0f;
    sf::Keyboard::Scan::Scancode directionKeys[4];
public:
    bool onGround = false;
    unsigned int score = 0;
    Sprite *sprite;
    Player(ControlType controlType, sf::Texture &texture, float startX, float startY, CollisionType collisionType);
    ~Player();

    void manageMovement(InputHandler *inputHandler, sf::Time dt);
    void move(sf::Vector2f vec);
    void resetVelocity();
    void resetGravity();
    void setPosition(sf::Vector2f vec);
    sf::Vector2f getPosition();
};