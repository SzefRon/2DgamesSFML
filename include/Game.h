#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "MousePlayer.h"
#include "InputHandler.h"
#include "LevelLoader.h"

class Game
{
private:
    InputHandler *inputHandler;
    sf::RenderWindow *window;
    sf::Time dt;
    Player *player1;
    MousePlayer *player2;
    LevelLoader *levelLoader;
public:
    Game(unsigned int initSizeX, unsigned int initSizeY);
    ~Game();
    void start();
};