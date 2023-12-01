#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <deque>

#include "Player.h"
#include "Maths.h"

class Game;

class Camera
{
public:
    sf::View *view;

    Camera(unsigned int screenX, unsigned int screenY);
    void moveCameraBox(Player *player);
    void moveCameraSmooth(Player *player, sf::Time dt);
    void snapCamera(Player *player);
    float followPlayersSmooth(std::deque<Player *> &players, sf::Time dt, unsigned int windowX, unsigned int windowY);
    float snapPlayers(std::deque<Player *> &players, unsigned int windowX, unsigned int windowY);
};