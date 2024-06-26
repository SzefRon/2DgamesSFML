#pragma once

#include <deque>
#include <tuple>

#include "Player.h"
#include "Maths.h"

class CollisionManager
{
public:
    static bool managePlayerCollision(Player *player, std::deque<Sprite *> &sprites, bool separate);
};