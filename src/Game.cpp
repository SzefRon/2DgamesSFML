#include "Game.h"

void Game::draw(sf::RenderTarget *target)
{
    for (auto &player : players) {
        target->draw(*(player->sprite->sprite));
    }

    for (auto &sprite : levelLoader->sprites) {
        target->draw(*(sprite->sprite));
    }

    for (auto &followArrow : followArrows) {
        if (followArrow->draw) {
            target->draw(*followArrow->sprite);
        }
    }

    target->draw(*(goal.at(0)->sprite));
}

void Game::manageFollowArrows(Player *player, FollowArrow *followArrow, sf::Sprite *goal)
{
    sf::Vector2f playerPos = player->getPosition();
    sf::Vector2f diff = playerPos - goal->getPosition();
    float diffLen = Maths::len(diff);

    if (diffLen <= 500.0f) followArrow->draw = false;
    else followArrow->draw = true;

    diff /= diffLen;
    diff *= 150.0f;
    followArrow->sprite->setPosition(playerPos - diff);
}

void Game::prepareLevel1()
{
    levelLoader->read(".\\res\\levels\\mazes\\maze1.json");
    for (auto &player : players) {
        int randX = Maths::randInt(0, 9);
        int randY = Maths::randInt(0, 9);
        player->setPosition(sf::Vector2f(randX * 384.0f + 256.0f, randY * 384.0f + 256.0f));
    }
    while (true) {
        int randX = Maths::randInt(0, 9);
        int randY = Maths::randInt(0, 9);
        sf::Vector2f newPos(randX * 384.0f + 256.0f, randY * 384.0f + 256.0f);
        float distPlayer1 = Maths::len(players.at(0)->getPosition() - newPos);
        float distPlayer2 = Maths::len(players.at(1)->getPosition() - newPos);

        if (fabs(distPlayer1 - distPlayer2) >= 500.0f
            || distPlayer1 <= 2000.0f) continue;

        goal.at(0)->sprite->setPosition(newPos);
        break;
    }
}

void Game::prepareLevel2()
{
    levelLoader->read(".\\res\\levels\\mazes\\maze2.json");
    for (auto &player : players) {
        int randX = Maths::randInt(0, 14);
        int randY = Maths::randInt(0, 14);
        player->setPosition(sf::Vector2f(randX * 256.0f + 192.0f, randY * 256.0f + 192.0f));
    }
    while (true) {
        int randX = Maths::randInt(0, 14);
        int randY = Maths::randInt(0, 14);
        sf::Vector2f newPos(randX * 256.0f + 192.0f, randY * 256.0f + 192.0f);
        float distPlayer1 = Maths::len(players.at(0)->getPosition() - newPos);
        float distPlayer2 = Maths::len(players.at(1)->getPosition() - newPos);

        if (fabs(distPlayer1 - distPlayer2) >= 300.0f
            || distPlayer1 <= 2000.0f) continue;

        goal.at(0)->sprite->setPosition(newPos);
        break;
    }
}

void Game::prepareLevel3()
{
    levelLoader->read(".\\res\\levels\\mazes\\maze3.json");
    for (auto &player : players) {
        int randX = Maths::randInt(0, 22);
        int randY = Maths::randInt(0, 22);
        player->setPosition(sf::Vector2f(randX * 256.0f + 192.0f, randY * 256.0f + 192.0f));
    }
    while (true) {
        int randX = Maths::randInt(0, 22);
        int randY = Maths::randInt(0, 22);
        sf::Vector2f newPos(randX * 256.0f + 192.0f, randY * 256.0f + 192.0f);
        float distPlayer1 = Maths::len(players.at(0)->getPosition() - newPos);
        float distPlayer2 = Maths::len(players.at(1)->getPosition() - newPos);

        if (fabs(distPlayer1 - distPlayer2) >= 300.0f
            || distPlayer1 <= 3000.0f) continue;

        goal.at(0)->sprite->setPosition(newPos);
        break;
    }
}

void Game::win(Player *player)
{
    player->score += 1;
    for (auto &player : players) {
        player->resetVelocity();
    }
    switch (level) {
        case 1: {
            level = 2;
            pause = true;
            std::thread thread([this](){
                std::this_thread::sleep_for(std::chrono::seconds(2));
                this->prepareLevel2();
                this->pause = false;
            });
            thread.detach();
            break;
        }
        case 2: {
            level = 3;
            pause = true;
            std::thread thread([this](){
                std::this_thread::sleep_for(std::chrono::seconds(2));
                this->prepareLevel3();
                this->pause = false;
            });
            thread.detach();
            break;
        }
        case 3: {
            level = 1;
            pause = true;
            std::thread thread([this](){
                std::this_thread::sleep_for(std::chrono::seconds(2));
                this->prepareLevel1();
                this->pause = false;
                for (auto &player : this->players) {
                    player->score = 0;
                }
            });
            thread.detach();
            break;
        }
    }
}

void Game::managePlayers()
{
    for (auto &player : players) {
        player->manageMovement(inputHandler, dt);
        CollisionManager::managePlayerCollision(player, levelLoader->sprites, true);

        if (CollisionManager::managePlayerCollision(player, goal, false)) {
            win(player);
        }
    }
}

void Game::manageDrawing()
{
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

void Game::drawScore(sf::RenderTarget *target)
{
    std::stringstream ss;
    ss << "SQUARE " << players.at(0)->score << " : " << players.at(1)->score << " CIRCLE";
    scoreText.setString(ss.str());
    scoreText.setPosition(target->getView().getSize().x * 0.5f - scoreText.getLocalBounds().width * 0.5f,
                          target->getView().getSize().y * 0.5f - scoreText.getLocalBounds().height);
    target->draw(scoreText);
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
    players.push_back(new Player(WASD, *texture, 0, 0, SQUARE));
    sf::Texture *texture2 = new sf::Texture();
    texture2->loadFromFile(".\\res\\textures\\player2.png");
    players.push_back(new Player(Arrows, *texture2, 128, 128, CIRCLE));

    sf::Texture *goalTexture = new sf::Texture();
    goalTexture->loadFromFile(".\\res\\textures\\goal.png");
    sf::Sprite *goalSprite = new sf::Sprite(*goalTexture);
    goalSprite->setScale(sf::Vector2f(1.0f, 1.0f));
    goalSprite->setOrigin(sf::Vector2f(64.0f, 64.0f));
    goal.push_back(new Sprite(goalSprite, SQUARE));

    sf::Texture *followArrowTexture = new sf::Texture();
    followArrowTexture->loadFromFile(".\\res\\textures\\follow-point.png");

    sf::Sprite *followArrow1 = new sf::Sprite(*followArrowTexture);
    followArrow1->setScale(sf::Vector2f(1.0f, 1.0f));
    followArrow1->setOrigin(sf::Vector2f(64.0f, 64.0f));
    sf::Sprite *followArrow2 = new sf::Sprite(*followArrowTexture);
    followArrow2->setScale(sf::Vector2f(1.0f, 1.0f));
    followArrow2->setOrigin(sf::Vector2f(64.0f, 64.0f));

    followArrows.push_back(new FollowArrow(followArrow1));
    followArrows.push_back(new FollowArrow(followArrow2));

    cameraManager = new CameraManager(players, initSizeX, initSizeY);

    levelLoader = new LevelLoader();

    defaultFont.loadFromFile(".\\res\\fonts\\Alef-Regular.ttf");
    scoreText.setCharacterSize(100);
    scoreText.setFont(defaultFont);
    scoreText.setString("0 : 0");

    prepareLevel1();
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

        if (!pause) {
            managePlayers();

            manageFollowArrows(players.at(0), followArrows.at(0), goal.at(0)->sprite);
            manageFollowArrows(players.at(1), followArrows.at(1), goal.at(0)->sprite);

            cameraManager->update(dt);

            window->clear(sf::Color(100, 100, 100));

            manageDrawing();
        } 
        else {
            window->setView(*(cameraManager->uiCamera->view));
            window->clear(sf::Color(100, 100, 100));

            drawScore(window);
        }

        window->display();
    }
}
