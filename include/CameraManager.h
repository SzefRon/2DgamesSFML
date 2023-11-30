#pragma once

#include <deque>

#include "Player.h"
#include "Camera.h"

enum CameraMode
{
    CONNECTED,
    SPLIT
};

class CameraManager
{
private:
    int windowX, windowY;
    float returnScale = 1.0f;
    bool direction;
    std::deque<Player *> players;
public:
    Camera *mainCamera;
    Camera *splitCamera1;
    Camera *splitCamera2;
    CameraMode cameraMode;
    CameraManager(std::deque<Player *> players, int initSizeX, int initSizeY);

    void update(sf::Time dt);
};