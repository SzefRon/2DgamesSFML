#include "Game.h"

void Game::draw()
{
    for (auto &player : players) {
        window->draw(*(player->sprite));
    }

    levelLoader->draw(window);
    kulkiManager->draw(window);
}

Game::Game(unsigned int initSizeX, unsigned int initSizeY)
{
    windowX = initSizeX;
    windowY = initSizeY;
    window = new sf::RenderWindow{{ initSizeX, initSizeY }, "Zadanie!", sf::Style::Close};
    window->setFramerateLimit(120);

    inputHandler = new InputHandler(window);

    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("..\\..\\res\\textures\\player1.png");
    players.push_back(new Player(WASD, *texture, 0, 0));
    sf::Texture *texture2 = new sf::Texture();
    texture2->loadFromFile("..\\..\\res\\textures\\player2.png");
    players.push_back(new Player(Arrows, *texture2, 128, 128));

    cameraManager = new CameraManager(players, initSizeX, initSizeY);

    levelLoader = new LevelLoader();
    levelLoader->read("..\\..\\res\\levels\\level1.json");

    kulkiManager = new KulkiManager(50, initSizeX, initSizeY);
    
    font = new sf::Font();
    font->loadFromFile("..\\..\\res\\fonts\\arial.ttf");
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

        cameraManager->update(dt);

        window->clear(sf::Color(100, 100, 100));

        /*if (cameraManager->cameraMode == CONNECTED) {
            window->setView(*(cameraManager->mainCamera->view));
            draw();
        }
        else if (cameraManager->cameraMode = SPLIT) {
            window->setView(*(cameraManager->splitCamera2->view));
            draw();
            window->setView(*(cameraManager->splitCamera1->view));
            draw();
        }*/

        sf::Vector2f cameraPos = cameraManager->mainCamera->view->getCenter();
        sf::Vector2f cameraSize = cameraManager->mainCamera->view->getSize();
        kulkiManager->update(inputHandler->keyboardToggles ,cameraPos, cameraSize, dt);

        window->setView(*(cameraManager->mainCamera->view));
        draw();

        window->setView(*(cameraManager->uiCamera->view));
        std::stringstream ss;
        ss << "Odsuwanie: " << inputHandler->keyboardToggles[sf::Keyboard::Scan::Scancode::E]
            << "\nOdbicia: " << inputHandler->keyboardToggles[sf::Keyboard::Scan::Scancode::R];
        sf::Text text(ss.str(), *font);
        text.setPosition(0.0f, 0.0f);
        window->draw(text);

        window->display();
    }
}
