#include "CameraManager.h"

CameraManager::CameraManager(std::deque<Player *> players, int initSizeX, int initSizeY)
    : players(players), windowX(initSizeX), windowY(initSizeY)
{
    mainCamera = new Camera(initSizeX, initSizeY);
    splitCamera1 = new Camera(initSizeX, initSizeY);
    splitCamera2 = new Camera(initSizeX, initSizeY);
}

void CameraManager::update(sf::Time dt)
{
    float playerDistance = 0.0f;
    sf::Vector2f playerPos1 = players[0]->getPos();
    sf::Vector2f playerPos2 = players[1]->getPos();
    //playerDistance = std::sqrtf((playerPos1.x - playerPos2.x) * (playerPos1.x - playerPos2.x) + (playerPos1.y - playerPos2.y) * (playerPos1.y - playerPos2.y));

    playerDistance = mainCamera->followPlayers(players, dt, windowX, windowY);

    if (playerDistance >= 2.5f) {
        splitCamera1->moveCameraSmooth(players.at(0), dt);
        splitCamera2->moveCameraSmooth(players.at(1), dt);

        splitCamera1->view->setSize(windowX * 2.5f, windowY * 2.5f);
        splitCamera2->view->setSize(windowX * 2.5f, windowY * 2.5f);

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

        if (playerPos1.x < playerPos2.x) {
            direction = true;
            splitCamera1->view->setCenter(sf::Vector2f(center.x - size.x * 0.25f, center.y));
            splitCamera2->view->setCenter(sf::Vector2f(center.x + size.x * 0.25f, center.y));
        }
        else {
            direction = false;
            splitCamera1->view->setCenter(sf::Vector2f(center.x + size.x * 0.25f, center.y));
            splitCamera2->view->setCenter(sf::Vector2f(center.x - size.x * 0.25f, center.y));
        }
        
        cameraMode = CONNECTED;
    }
}
