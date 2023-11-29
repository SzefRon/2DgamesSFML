#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>

#include "Player.h"
#include "MousePlayer.h"
#include "InputHandler.h"
#include "LevelLoader.h"
#include "CameraManager.h"
#include "KulkiManager.h"

class Game
{
private:
    int windowX, windowY;
    InputHandler *inputHandler;
    sf::RenderWindow *window;
    sf::Time dt;
    std::deque<Player *> players;
    LevelLoader *levelLoader;
    CameraManager *cameraManager;
    KulkiManager *kulkiManager;
    sf::Font *font;

    void draw();
public:
    Game(unsigned int initSizeX, unsigned int initSizeY);
    ~Game();
    void start();
};