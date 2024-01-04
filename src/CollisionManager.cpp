#include "CollisionManager.h"

bool CollisionManager::managePlayerCollision(Player *player, std::deque<Sprite *> &sprites, bool separate)
{
    bool returnVal = false;
    switch (player->sprite->collisionType) {
        case SQUARE: {
            std::deque<std::tuple<Sprite *, sf::Vector2f>> collidingSprites;
            do {
                collidingSprites.clear();
                for (auto &sprite : sprites) {
                    sf::Vector2f blockPos = sprite->sprite->getPosition();
                    sf::Vector2f playerPos = player->getPosition();
                    sf::Vector2f diff(blockPos.x - playerPos.x, blockPos.y - playerPos.y);
                    if (fabs(diff.x) < 128.0f && fabs(diff.y) < 128.0f) {
                        collidingSprites.push_back({sprite, diff});
                        returnVal = true;
                    }
                }
                if (separate && collidingSprites.size() > 0) {
                    std::sort(collidingSprites.begin(), collidingSprites.end(),
                        [](std::tuple<Sprite *, sf::Vector2f> a, std::tuple<Sprite *, sf::Vector2f> b) {
                            sf::Vector2f aDiff = std::get<1>(a);
                            sf::Vector2f bDiff = std::get<1>(b);
                            return fabs(aDiff.x) + fabs(aDiff.y) < fabs(bDiff.x) + fabs(bDiff.y);
                        });
                    auto &sprite = collidingSprites.at(0);
                    sf::Vector2f diff = std::get<1>(sprite);
                    if (fabs(diff.x) > fabs(diff.y)) {
                        player->move(sf::Vector2f(diff.x - Maths::sign(diff.x) * 128.0f, 0.0f));
                    }
                    else {
                        player->move(sf::Vector2f(0.0f, diff.y - Maths::sign(diff.y) * 128.0f));
                        player->resetGravity();
                        if (Maths::sign(diff.y) == 1) {
                            player->onGround = true;
                        } 
                    }
                }
            } while (collidingSprites.size() > 0);
            break;
        }
        case CIRCLE: {
            for (auto &sprite : sprites) {
                sf::Vector2f blockPos = sprite->sprite->getPosition();
                sf::Vector2f playerPos = player->getPosition();
                sf::Vector2f closestPoint(Maths::clamp(playerPos.x, blockPos.x - 64.0f, blockPos.x + 64.0f),
                                          Maths::clamp(playerPos.y, blockPos.y - 64.0f, blockPos.y + 64.0f));
                sf::Vector2f diff = playerPos - closestPoint;
                if (diff.x == 0.0f && diff.y == 0.0f) {
                    // TODO: Implement full overlap collision between circle and square
                    if (separate) {

                    }
                    returnVal = true;
                }
                else {
                    float distance = Maths::len(diff);
                    if (distance < 64.0f) {
                        if (separate) {
                            float scalar = 64.0f - distance;
                            float x = (diff.x / distance) * scalar;
                            float y = (diff.y / distance) * scalar;
                            if (x == 0.0f) {
                                player->resetGravity();
                                if (Maths::sign(y) == -1) player->onGround = true;
                            }
                                
                            player->move(sf::Vector2f(x, y));
                        }
                        returnVal = true;
                    }
                }
            }
            break;
        }
    }
    return returnVal;
}