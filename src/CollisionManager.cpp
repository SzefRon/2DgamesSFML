#include "CollisionManager.h"

bool CollisionManager::managePlayerCollision(Player *player, std::deque<Sprite *> &sprites, bool separate)
{
    bool returnVal = false;
    switch (player->sprite->collisionType) {
        case SQUARE: {
            for (auto &sprite : sprites) {
                sf::Vector2f blockPos = sprite->sprite->getPosition();
                sf::Vector2f playerPos = player->getPosition();
                sf::Vector2f diff(blockPos.x - playerPos.x, blockPos.y - playerPos.y);
                if (fabs(diff.x) < 128.0f && fabs(diff.y) < 128.0f) {
                    if (separate) {
                        if (fabs(diff.x) > fabs(diff.y)) {
                            player->move(sf::Vector2f(diff.x - Maths::sign(diff.x) * 128.0f, 0.0f));
                        }
                        else {
                            player->move(sf::Vector2f(0.0f, diff.y - Maths::sign(diff.y) * 128.0f));
                        }
                    }
                    returnVal = true;
                }
            }
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
                            player->move(sf::Vector2f((diff.x / distance) * scalar, (diff.y / distance) * scalar));
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