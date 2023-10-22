#include "LevelLoader.h"

bool LevelLoader::read(std::string filePath)
{
    std::ifstream file;
    std::stringstream ss;

    file.open(filePath);
    
    if (file.is_open()) {
        file >> ss.rdbuf();
        file.close();
    }
    else {
        return 1;
    }

    std::string str = ss.str();
    char * fileContent = new char [str.length()+1];
    strcpy(fileContent, str.c_str());

    document.Parse(fileContent);

    for (auto &object : document["level"].GetArray()) {
        std::string textureFilePath = "..\\..\\res\\textures\\";
        textureFilePath.append(object["texture"].GetString());
        
        sf::Texture *texture = new sf::Texture();
        texture->loadFromFile(textureFilePath);
        
        sf::Sprite *sprite = new sf::Sprite(*texture);
        sprite->scale(1.0f, 1.0f);
        auto positionObj = object["pos"].GetArray();
        sprite->setPosition(sf::Vector2f(positionObj[0].GetInt() * 128, positionObj[1].GetInt() * 128));
        
        if (strcmp(object["type"].GetString(), "triangle") == 0) {
            float angle = object["rotation"].GetInt() * 90.0f;
            sprite->setOrigin(sf::Vector2f(64.0f, 64.0f));
            sprite->setRotation(angle);
            sprite->move(64.0f, 64.0f);
        }

        sprites.push_back(sprite);
    }

    return 0;
}

void LevelLoader::draw(sf::RenderWindow *window)
{
    for (auto sprite : sprites) {
        window->draw(*sprite);
    }
}
