#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <math.h>
#include <thread>

#include "Player.h"
#include "MousePlayer.h"
#include "InputHandler.h"
#include "LevelLoader.h"
#include "CameraManager.h"
#include "CollisionManager.h"

struct FollowArrow
{
    sf::Sprite *sprite;
    bool draw = true;

    FollowArrow(sf::Sprite *sprite)
        : sprite(sprite) {}
};

class Game
{
private:
    int windowX, windowY;
    InputHandler *inputHandler;
    sf::RenderWindow *window;
    sf::RenderWindow *UIwindow;

    sf::RenderTexture frameBuff1, frameBuff2;
    sf::Shader fbShader;
    sf::Texture frameTex1, frameTex2;

    std::deque<Player *> players;
    std::deque<Sprite *> goal;
    std::deque<FollowArrow *> followArrows;

    sf::Time dt;
    LevelLoader *levelLoader;
    CameraManager *cameraManager;
    sf::Font defaultFont;
    sf::Text scoreText;
    int level = 1;
    bool pause = false;

    void prepareLevel1();
    void prepareLevel2();
    void prepareLevel3();

    void draw(sf::RenderTarget *target);
    void manageFollowArrows(Player *player, FollowArrow *followArrow, sf::Sprite *goal);
    void win(Player *player);
    void managePlayers();
    void manageDrawing();
    void drawScore(sf::RenderTarget *target);
public:
    Game(unsigned int initSizeX, unsigned int initSizeY);
    ~Game();
    void start();
};