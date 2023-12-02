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

    frameBuff1.create(initSizeX * 2.0f, initSizeY * 2.0f);
    frameBuff2.create(initSizeX * 2.0f, initSizeY * 2.0f);
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

            sf::Vector2f diff = players[1]->getPos() - players[0]->getPos();
            float a = -1.0f * (diff.x / (abs(diff.y) <= 0.0001f ? 0.0001f : diff.y));

            diff.x = (diff.x / 1600.0f) * 0.25f;
            diff.y = (diff.y / 900.0f) * 0.25f;

            float aScaled = -1.0f * (diff.x / (abs(diff.y) <= 0.0001f ? 0.0001f : diff.y));
            
            diff.x = Maths::sign(diff.x) * Maths::min(0.25f, abs(diff.x));
            diff.y = Maths::sign(diff.y) * Maths::min(0.25f, abs(diff.y));

            fbShader.setUniform("tex1", frameTex1);
            fbShader.setUniform("tex2", frameTex2);
            fbShader.setUniform("diffVec", sf::Vector2f(diff.x, diff.y));
            fbShader.setUniform("a", a);

            sf::RectangleShape rect(sf::Vector2f(windowX, windowY));
            rect.setTexture(&frameTex1, true);
            rect.setPosition(0.0f, 0.0f);

            sf::RectangleShape line(sf::Vector2f(2000.0f, 5.0f));
            line.setOrigin(sf::Vector2f(1000.0f, 2.5f));
            line.setFillColor(sf::Color(0, 0, 0));
            line.setPosition(sf::Vector2f(windowX * 0.5f, windowY * 0.5f));
            line.rotate(std::atanf(aScaled) * 57.29578f);

            window->setView(*(cameraManager->uiCamera->view));
            window->draw(rect, &fbShader);
            window->draw(line);
        }

        window->display();
    }
}
