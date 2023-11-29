#include "CameraManager.h"

CameraManager::CameraManager(std::deque<Player *> players, int initSizeX, int initSizeY)
    : players(players), windowX(initSizeX), windowY(initSizeY)
{
    mainCamera = new Camera(initSizeX, initSizeY);
    uiCamera = new Camera(initSizeX, initSizeY);
    splitCamera1 = new Camera(initSizeX / 2, initSizeY);
    splitCamera2 = new Camera(initSizeX / 2, initSizeY);
}

void CameraManager::update(sf::Time dt)
{
    float playerDistance = 0.0f;
    sf::Vector2f playerPos1 = players[0]->getPos();
    sf::Vector2f playerPos2 = players[1]->getPos();
    playerDistance = std::sqrtf((playerPos1.x - playerPos2.x) * (playerPos1.x - playerPos2.x) + (playerPos1.y - playerPos2.y) * (playerPos1.y - playerPos2.y));

    float returnScale = mainCamera->followPlayers(players, dt, windowX, windowY);
    splitCamera1->moveCameraSmooth(players.at(0), dt);
    splitCamera2->moveCameraSmooth(players.at(1), dt);

    if (playerDistance >= 1500.0f) {
        cameraMode = SPLIT;
        splitCamera1->view->setSize(windowX * returnScaleUpdated / 2, windowY * returnScaleUpdated);
        splitCamera2->view->setSize(windowX * returnScaleUpdated / 2, windowY * returnScaleUpdated);

        if (playerPos1.x < playerPos2.x) {
            splitCamera1->view->setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
            splitCamera2->view->setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
        }
        else {
            splitCamera1->view->setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
            splitCamera2->view->setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
        }
    }
    else {
        cameraMode = CONNECTED;
        returnScaleUpdated = returnScale;
    }
}
