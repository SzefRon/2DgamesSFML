#include "LevelLoader.h"

bool LevelLoader::read(std::string filePath)
{
    sprites.clear();
    blockPalette.clear();
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
    char *fileContent = new char[str.length()];
    strcpy(fileContent, str.c_str());

    document.Parse(fileContent);

    std::string textureFilePath = ".\\res\\textures\\";
    for (auto &object : document["palette"].GetArray()) {
        Block block;
        std::string collisionType = object["type"].GetString();

        if (collisionType == "square") block.collisionType = SQUARE; 

        sf::Texture *texture = new sf::Texture();
        texture->loadFromFile(textureFilePath + object["texture"].GetString());
        block.texture = texture;

        std::string name = object["name"].GetString();
        blockPalette.emplace(name, block);
    }

    for (auto &object : document["level"].GetArray()) {
        std::string name = object["name"].GetString();
        const Block &block = blockPalette[name];
        
        sf::Sprite *sprite = new sf::Sprite(*block.texture);
        sf::Vector2u texSize = block.texture->getSize();
        auto positionObj = object["pos"].GetArray();
        sprite->setPosition(sf::Vector2f(positionObj[0].GetInt() * 128, positionObj[1].GetInt() * 128));

        float angle = object["rotation"].GetInt() * 90.0f;
        sprite->setOrigin(sf::Vector2f(texSize.x * 0.5f, texSize.y * 0.5f));
        sprite->setRotation(angle);
        sprite->move(texSize.x * 0.5f, texSize.y * 0.5f);
        sprite->setScale(128.0f / texSize.x, 128.0f / texSize.y);

        sprites.push_back(new Sprite(sprite, block.collisionType));
    }

    return 0;
}
