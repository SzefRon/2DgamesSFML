#include "Game.h"

Game::Game(unsigned int initSizeX, unsigned int initSizeY)
{
    window = new sf::RenderWindow{{ initSizeX, initSizeY }, "Zadanie!", sf::Style::Close};
    window->setFramerateLimit(120);

    inputHandler = new InputHandler(window);
    camera = new Camera(initSizeX, initSizeY);

    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("..\\..\\res\\textures\\player1.png");
    player1 = new Player(*texture, 64, 64);
    /*sf::Texture *texture2 = new sf::Texture();
    texture2->loadFromFile("..\\..\\res\\textures\\player2.png");
    player2 = new MousePlayer(*texture2, 256, 256);*/

    levelLoader = new LevelLoader();
    levelLoader->read("..\\..\\res\\levels\\level1.json");
}

Game::~Game()
{
    delete window;
}

void Game::start()
{
    sf::Clock clock;
    while (window->isOpen()) {
        dt = clock.restart();
        inputHandler->handleEvents();

        //player2->move(inputHandler->mouseInputs, inputHandler->mousePos, dt);
        player1->move(inputHandler->keyboardInputs, dt);

        camera->moveCameraBox(player1);
        camera->moveCameraSmooth(player1, dt);
        window->setView(*(camera->view));

        window->clear(sf::Color(100, 100, 100));
        window->draw(*(player1->sprite));
        //window->draw(*(player2->sprite));

        levelLoader->draw(window);
        window->display();
    }
}
