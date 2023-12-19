#include "CameraManager.h"

CameraManager::CameraManager(std::deque<Player *> players, int initSizeX, int initSizeY)
    : players(players), windowX(initSizeX), windowY(initSizeY)
{
    mainCamera = new Camera(initSizeX, initSizeY);
    uiCamera = new Camera(initSizeX, initSizeY);
    splitCamera1 = new Camera(initSizeX, initSizeY);
    splitCamera2 = new Camera(initSizeX, initSizeY);
}

void CameraManager::update(sf::Time dt)
{
    float playerDistance = 0.0f;
    sf::Vector2f playerPos1 = players[0]->getPosition();
    sf::Vector2f playerPos2 = players[1]->getPosition();
    //playerDistance = std::sqrtf((playerPos1.x - playerPos2.x) * (playerPos1.x - playerPos2.x) + (playerPos1.y - playerPos2.y) * (playerPos1.y - playerPos2.y));

    playerDistance = mainCamera->snapPlayers(players, windowX, windowY);

    if (playerDistance >= 2.5f) {
        splitCamera1->snapCamera(players.at(0));
        splitCamera2->snapCamera(players.at(1));

        splitCamera1->view->setSize(windowX * 5.0f, windowY * 5.0f);
        splitCamera2->view->setSize(windowX * 5.0f, windowY * 5.0f);

        if (direction) {
            //splitCamera1->view->setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
            //splitCamera2->view->setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
        }
        else {
            //splitCamera1->view->setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
            //splitCamera2->view->setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
        }
        cameraMode = SPLIT;
    }
    else {
        sf::Vector2f center = mainCamera->view->getCenter();
        sf::Vector2f size = mainCamera->view->getSize();

        sf::Vector2f diff = playerPos2 - playerPos1;
        float diffLen = std::sqrtf(diff.x * diff.x + diff.y * diff.y);
        diff.x = (diff.x / diffLen) * 0.25f;
        diff.y = (diff.y / diffLen) * 0.25f;

        direction = true;
        splitCamera1->view->setCenter(sf::Vector2f(center.x - size.x * diff.x, center.y - size.y * diff.y));
        splitCamera2->view->setCenter(sf::Vector2f(center.x + size.x * diff.x, center.y + size.y * diff.y));
        
        cameraMode = CONNECTED;
    }
}
