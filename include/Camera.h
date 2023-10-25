#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

#include "Player.h"
#include "Maths.h"

class Camera
{
public:
    sf::View *view;

    Camera(unsigned int screenX, unsigned int screenY);
    void moveCameraBox(Player *player);
    void moveCameraSmooth(Player *player, sf::Time dt);
};