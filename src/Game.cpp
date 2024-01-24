#include "Game.h"

void Game::draw(sf::RenderTarget *target)
{
    for (int i = 0; i < backgrounds.size(); i++) {
        if (i == 3) {
            for (auto &player : players) {
                target->draw(*(player->sprite->sprite));
            }
        }
        if (i == 5) {
            for (auto &sprite : levelLoader->sprites) {
                target->draw(*(sprite->sprite));
            }
        }
        for (auto &sprite : backgrounds[i]->sprites) {
            target->draw(*sprite);
        }
    }

    for (auto &followArrow : followArrows) {
        if (followArrow->draw) {
            target->draw(*followArrow->sprite);
        }
    }
}

void Game::managePlayers()
{
    for (auto &player : players) {
        player->manageMovement(inputHandler, dt);
        CollisionManager::managePlayerCollision(player, levelLoader->sprites, true);

        std::deque<Sprite *> otherPlayerSprites;
        for (auto &otherPlayer : players) {
            if (otherPlayer == player) continue;
            Sprite *newSprite = new Sprite(otherPlayer->sprite->sprite, SQUARE);
            otherPlayerSprites.push_back(newSprite);
        }
        CollisionManager::managePlayerCollision(player, otherPlayerSprites, true);
        for (auto &otherPlayerSprite : otherPlayerSprites) {
            delete otherPlayerSprite;
        }
    }
}

void Game::manageDrawing()
{
    if (cameraManager->cameraMode == CONNECTED) {
        cameraOffset = cameraOffset - cameraManager->mainCamera->view->getCenter();
        for (auto &background : backgrounds) {
            background->update(cameraOffset);
        }
        cameraOffset = cameraManager->mainCamera->view->getCenter();
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

        sf::Vector2f diff = players[1]->getPosition() - players[0]->getPosition();
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
    texture->loadFromFile(".\\res\\textures\\foxel.png");
    players.push_back(new Player(WASD, *texture, 22.0f * 128.0f, 22.0f * 128.0f, CIRCLE));
    sf::Texture *texture2 = new sf::Texture();
    texture2->loadFromFile(".\\res\\textures\\rab-bit.png");
    players.push_back(new Player(Arrows, *texture2, 23.0f * 128.0f, 22.0f * 128.0f, CIRCLE));

    sf::Texture *followArrowTexture = new sf::Texture();
    followArrowTexture->loadFromFile(".\\res\\textures\\follow-point.png");

    cameraManager = new CameraManager(players, initSizeX, initSizeY);

    levelLoader = new LevelLoader();
    levelLoader->read(".\\res\\levels\\level3.json");

    defaultFont.loadFromFile(".\\res\\fonts\\Alef-Regular.ttf");
    scoreText.setCharacterSize(100);
    scoreText.setFont(defaultFont);
    scoreText.setString("0 : 0");

    sf::Texture *tempTexture;
    sf::Sprite *tempSrite;

    tempTexture = new sf::Texture();
    tempTexture->loadFromFile(".\\res\\textures\\building2.png");
    tempSrite = new sf::Sprite((*tempTexture));
    tempSrite->setScale(16.0f, 16.0f);
    backgrounds.push_back(new Background(0.3f, 100.0f, 17.62f * 128.0f, 50, tempSrite));

    tempTexture = new sf::Texture();
    tempTexture->loadFromFile(".\\res\\textures\\building.png");
    tempSrite = new sf::Sprite((*tempTexture));
    tempSrite->setScale(18.0f, 18.0f);
    backgrounds.push_back(new Background(0.2f, 200.0f, 16.62f * 128.0f, 40, tempSrite));

    tempTexture = new sf::Texture();
    tempTexture->loadFromFile(".\\res\\textures\\pile_of_trash.png");
    tempSrite = new sf::Sprite((*tempTexture));
    tempSrite->setScale(5.0f, 5.0f);
    backgrounds.push_back(new Background(0.15f, 3000.0f, 24.4f * 128.0f, 20, tempSrite));

    tempTexture = new sf::Texture();
    tempTexture->loadFromFile(".\\res\\textures\\trash_bin.png");
    tempSrite = new sf::Sprite((*tempTexture));
    tempSrite->setScale(6.0f, 6.0f);
    backgrounds.push_back(new Background(0.15f, 2000.0f, 24.15f * 128.0f, 20, tempSrite));

    tempTexture = new sf::Texture();
    tempTexture->loadFromFile(".\\res\\textures\\lamp.png");
    tempSrite = new sf::Sprite((*tempTexture));
    tempSrite->setScale(14.0f, 14.0f);
    backgrounds.push_back(new Background(0.1f, 500.0f, 20.62f * 128.0f, 40, tempSrite));

    tempTexture = new sf::Texture();
    tempTexture->loadFromFile(".\\res\\textures\\car.png");
    tempSrite = new sf::Sprite((*tempTexture));
    tempSrite->setScale(8.0f, 8.0f);
    backgrounds.push_back(new Background(-2.0f, 5000.0f, 26.62f * 128.0f, 40, tempSrite));

    //prepareLevel1();
}

Game::~Game()
{
    delete window;
}

void Game::start()
{
    sf::Clock clock;
    sf::Vector2f cameraOffset = sf::Vector2f(0.0f, 0.0f);
    while (window->isOpen()) {
        dt = clock.restart();
        inputHandler->handleEvents();

        managePlayers();

        // manageFollowArrows(players.at(0), followArrows.at(0), goal.at(0)->sprite);
        // manageFollowArrows(players.at(1), followArrows.at(1), goal.at(0)->sprite);

        cameraManager->update(dt);

        window->clear(sf::Color(23, 26, 38));

        manageDrawing();

        window->display();
    }
}
