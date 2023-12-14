#pragma once

#include <SFML/Graphics.hpp>

#include "CollisionType.h"

struct Sprite
{
    sf::Sprite *sprite;
    CollisionType collisionType;

    Sprite(sf::Sprite *sprite, CollisionType collisionType)
        : sprite(sprite), collisionType(collisionType) {}
};