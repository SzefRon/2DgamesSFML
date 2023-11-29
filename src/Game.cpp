#include "Game.h"

Game::Game(unsigned int initSizeX, unsigned int initSizeY)
{
    windowX = initSizeX;
    windowY = initSizeY;
    window = new sf::RenderWindow{{ initSizeX, initSizeY }, "Zadanie!", sf::Style::Close};
    window->setFramerateLimit(120);

    inputHandler = new InputHandler(window);
    camera = new Camera(initSizeX, initSizeY);
    splitCamera1 = new Camera(initSizeX / 2, initSizeY);
    splitCamera2 = new Camera(initSizeX / 2, initSizeY);

    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("..\\..\\res\\textures\\player1.png");
    players.push_back(new Player(WASD, *texture, 0, 0));
    sf::Texture *texture2 = new sf::Texture();
    texture2->loadFromFile("..\\..\\res\\textures\\player2.png");
    players.push_back(new Player(Arrows, *texture2, 128, 128));

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

        for (auto &player : players) {
            player->move(inputHandler->keyboardInputs, dt);
        }

        float playerDistance = 0.0f;
        sf::Vector2f playerPos1 = players[0]->getPos();
        sf::Vector2f playerPos2 = players[1]->getPos();
        playerDistance = std::sqrtf((playerPos1.x - playerPos2.x) * (playerPos1.x - playerPos2.x) + (playerPos1.y - playerPos2.y) * (playerPos1.y - playerPos2.y));

        float returnScale = camera->followPlayers(players, dt, windowX, windowY);
        float returnScaleUpdated = 1.0f;
        splitCamera1->moveCameraSmooth(players.at(0), dt);
        splitCamera2->moveCameraSmooth(players.at(1), dt);

        if (playerDistance >= 1500.0f) {
            splitCamera1->view->setSize(windowX * returnScale / 2, windowY * returnScale);
            splitCamera1->view->setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
            window->setView(*(splitCamera1->view));

            window->clear(sf::Color(100, 100, 100));

            for (auto &player : players) {
                window->draw(*(player->sprite));
            }

            levelLoader->draw(window);

            splitCamera2->view->setSize(windowX * returnScale / 2, windowY * returnScale);
            splitCamera2->view->setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
            window->setView(*(splitCamera2->view));

            for (auto &player : players) {
                window->draw(*(player->sprite));
            }

            levelLoader->draw(window);

            window->display();
        }
        else {
            //camera->view->setViewport(sf::FloatRect(0.0f, 0.f, 0.5f, 1.f));
            window->setView(*(camera->view));

            window->clear(sf::Color(100, 100, 100));

            for (auto &player : players) {
                window->draw(*(player->sprite));
            }

            levelLoader->draw(window);
            window->display();
            returnScaleUpdated = returnScale;
        }
    }
}
