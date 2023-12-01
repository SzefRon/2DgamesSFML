#include "Camera.h"
#include <iostream>

Camera::Camera(unsigned int screenX, unsigned int screenY)
{
    view = new sf::View(sf::Vector2f(screenX / 2.0f, screenY / 2.0f), sf::Vector2f(screenX, screenY));
}

void Camera::moveCameraBox(Player *player)
{
    sf::Vector2f playerPos = player->getPos();
    sf::Vector2f cameraPos = view->getCenter();
    sf::Vector2f cameraOffset = sf::Vector2f(playerPos.x - cameraPos.x, playerPos.y - cameraPos.y);
    if (fabs(cameraOffset.x) > 100) {
        view->move(cameraOffset.x - Maths::sign(cameraOffset.x) * 100, 0.0f);
    }
    if (fabs(cameraOffset.y) > 100) {
        view->move(0.0f, cameraOffset.y - Maths::sign(cameraOffset.y) * 100);
    }
}

void Camera::moveCameraSmooth(Player *player, sf::Time dt)
{
    float vx = 0.0f, vy = 0.0f;
    sf::Vector2f playerPos = player->getPos();
    sf::Vector2f cameraPos = view->getCenter();
    sf::Vector2f cameraOffset = sf::Vector2f(playerPos.x - cameraPos.x, playerPos.y - cameraPos.y);
    
    float len = sqrtf(cameraOffset.x * cameraOffset.x + cameraOffset.y * cameraOffset.y);

    if (len > 1.0f) {
        float multiplier = sqrtf(len * 0.005f);
        vx = (cameraOffset.x / len) * multiplier;
        vy = (cameraOffset.y / len) * multiplier;
    }

    view->move(vx * dt.asMilliseconds(), vy * dt.asMilliseconds());
}

void Camera::snapCamera(Player *player)
{
    sf::Vector2f playerPos = player->getPos();
    view->setCenter(playerPos.x, playerPos.y);
}

float Camera::followPlayersSmooth(std::deque<Player *> &players, sf::Time dt, unsigned int windowX, unsigned int windowY)
{
    float vx = 0.0f, vy = 0.0f;

    sf::Vector2f playerAveragePos(0.0f, 0.0f);
    for (auto &player : players) {
        sf::Vector2f playerPos = player->getPos();
        playerAveragePos.x += playerPos.x;
        playerAveragePos.y += playerPos.y;
    }
    int noPlayers = players.size();
    playerAveragePos.x /= noPlayers;
    playerAveragePos.y /= noPlayers;

    sf::Vector2f cameraPos = view->getCenter();
    sf::Vector2f cameraOffset = sf::Vector2f(playerAveragePos.x - cameraPos.x, playerAveragePos.y - cameraPos.y);
    
    float len = sqrtf(cameraOffset.x * cameraOffset.x + cameraOffset.y * cameraOffset.y);

    if (len > 1.0f) {
        float multiplier = sqrtf(len * 0.005f);
        vx = (cameraOffset.x / len) * multiplier;
        vy = (cameraOffset.y / len) * multiplier;
    }

    view->move(vx * dt.asMilliseconds(), vy * dt.asMilliseconds());

    float furthestX = 0.0f, furthestY = 0.0f;
    for (auto &player : players) {
        sf::Vector2f playerPos = player->getPos();
        float x = abs(playerAveragePos.x - playerPos.x);
        float y = abs(playerAveragePos.y - playerPos.y);
        if (x > furthestX) furthestX = x;
        if (y > furthestY) furthestY = y;
    }

    float sizeX = ((furthestX + 0.5f * windowX) * 2.0f) / windowX;
    float sizeY = ((furthestY + 0.5f * windowY) * 2.0f) / windowY;

    if (sizeX > sizeY) {
        float scale = Maths::min<float>(Maths::max<float>(1.5f, sizeX), 2.5f);
        view->setSize(windowX * scale, windowY * scale);
        return scale;
    }
    else {
        float scale = Maths::min<float>(Maths::max<float>(1.5f, sizeY), 2.5f);
        view->setSize(windowX * scale, windowY * scale);
        return scale;
    }
}

float Camera::snapPlayers(std::deque<Player *> &players, unsigned int windowX, unsigned int windowY)
{
    sf::Vector2f playerAveragePos(0.0f, 0.0f);
    for (auto &player : players) {
        sf::Vector2f playerPos = player->getPos();
        playerAveragePos.x += playerPos.x;
        playerAveragePos.y += playerPos.y;
    }
    int noPlayers = players.size();
    playerAveragePos.x /= noPlayers;
    playerAveragePos.y /= noPlayers;

    view->setCenter(playerAveragePos.x, playerAveragePos.y);
    sf::Vector2f size = view->getSize();

    sf::Vector2f playerPos = players[0]->getPos();
    float diffX = abs(playerAveragePos.x - playerPos.x);
    float diffY = abs(playerAveragePos.y - playerPos.y);

    float newSizeX = (2.0f * diffX + size.x * 0.5f) / windowX;
    float newSizeY = (2.0f * diffY + size.y * 0.5f) / windowY;

    if (newSizeX > newSizeY) {
        float scale = Maths::min<float>(Maths::max<float>(1.5f, newSizeX), 2.5f);
        view->setSize(windowX * scale, windowY * scale);
        return scale;
    }
    else {
        float scale = Maths::min<float>(Maths::max<float>(1.5f, newSizeY), 2.5f);
        view->setSize(windowX * scale, windowY * scale);
        return scale;
    }
}
