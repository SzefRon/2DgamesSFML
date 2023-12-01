#include "Game.h"

void Game::draw(sf::RenderTarget *target)
{
    for (auto &player : players) {
        target->draw(*(player->sprite));
    }

    for (auto &sprite : levelLoader->sprites) {
        target->draw(*sprite);
    }
}

Game::Game(unsigned int initSizeX, unsigned int initSizeY)
{
    windowX = initSizeX;
    windowY = initSizeY;
    window = new sf::RenderWindow{{ initSizeX, initSizeY }, "Zadanie!", sf::Style::Close};
    window->setFramerateLimit(120);

    frameBuff1.create(initSizeX, initSizeY);
    frameBuff2.create(initSizeX, initSizeY);
    fbShader.loadFromFile(".\\res\\shaders\\frameBuff.frag", sf::Shader::Type::Fragment);

    inputHandler = new InputHandler(window);


    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile(".\\res\\textures\\player1.png");
    players.push_back(new Player(WASD, *texture, 0, 0));
    sf::Texture *texture2 = new sf::Texture();
    texture2->loadFromFile(".\\res\\textures\\player2.png");
    players.push_back(new Player(Arrows, *texture2, 128, 128));

    cameraManager = new CameraManager(players, initSizeX, initSizeY);

    levelLoader = new LevelLoader();
    levelLoader->read(".\\res\\levels\\level1.json");
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

        if (cameraManager->cameraMode == CONNECTED) {
            window->setView(*(cameraManager->mainCamera->view));
            draw(window);
        }
        else if (cameraManager->cameraMode = SPLIT) {
            frameBuff1.clear(sf::Color(100, 100, 100));
            frameBuff1.setView(*(cameraManager->splitCamera1->view));
            draw(&frameBuff1);
            frameBuff1.display();
            frameTex1 = frameBuff1.getTexture();

            frameBuff2.clear(sf::Color(100, 100, 100));
            frameBuff2.setView(*(cameraManager->splitCamera2->view));
            draw(&frameBuff2);
            frameBuff2.display();
            frameTex2 = frameBuff2.getTexture();

            sf::Texture tex;
            tex.loadFromFile(".\\res\\textures\\stone.png");

            fbShader.setUniform("tex1", frameTex1);
            fbShader.setUniform("tex2", frameTex2);

            sf::RectangleShape rect(sf::Vector2f(windowX, windowY));
            rect.setTexture(&frameTex1, true);
            rect.setPosition(0.0f, 0.0f);

            window->draw(rect, &fbShader);
        }

        window->display();
    }
}
