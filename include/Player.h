#pragma once

#include <SFML/Graphics.hpp>
#include <InputHandler.h>
#include <map>

#include "Sprite.h"

class Player
{
private:
    float x, y, speed = 1.0f, slipperiness = 0.99f;
    float vx = 0.f, vy = 0.f;
    sf::Keyboard::Scan::Scancode directionKeys[4];
public:
    Sprite *sprite;
    Player(ControlType controlType, sf::Texture &texture, float startX, float startY, CollisionType collisionType);
    ~Player();

    void manageMovement(std::map<sf::Keyboard::Scan::Scancode, bool> &keyboardInputs, sf::Time dt);
    void move(sf::Vector2f vec);
    void setPosition(sf::Vector2f vec);
    sf::Vector2f getPosition();
};