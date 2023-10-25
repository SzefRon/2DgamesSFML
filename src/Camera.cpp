#include "Camera.h"

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
        //view->move(0.0f, cameraOffset.y - Maths::sign(cameraOffset.y) * 100);
    }
}

void Camera::moveCameraSmooth(Player *player, sf::Time dt)
{
    float vx = 0.0f, vy = 0.0f;
    sf::Vector2f playerPos = player->getPos();
    sf::Vector2f cameraPos = view->getCenter();
    sf::Vector2f cameraOffset = sf::Vector2f(playerPos.x - cameraPos.x, playerPos.y - cameraPos.y);
    
    float len = sqrtf(cameraOffset.x * cameraOffset.x + cameraOffset.y * cameraOffset.y);

    float multiplier = sqrtf(len * 0.005f);
    vx = (cameraOffset.x / len) * multiplier;
    vy = (cameraOffset.y / len) * multiplier;

    view->move(0.0f, vy * dt.asMilliseconds());
}
