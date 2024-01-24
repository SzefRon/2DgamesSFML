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
#include "Background.h"

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

    sf::Vector2f cameraOffset = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f cameraOffset1 = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f cameraOffset2 = sf::Vector2f(0.0f, 0.0f);

    std::deque<Background *> backgrounds;

    void draw(sf::RenderTarget *target);
    void managePlayers();
    void manageDrawing();
public:
    Game(unsigned int initSizeX, unsigned int initSizeY);
    ~Game();
    void start();
};