#pragma once

#include <fstream>
#include <sstream>
#include <rapidjson/document.h>
#include <iostream>
#include <string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Sprite.h"

struct Block
{
    CollisionType collisionType;
    sf::Texture *texture;
};

class LevelLoader
{
private:
    rapidjson::Document document;
    std::unordered_map<std::string, Block> blockPalette;
public:
    std::deque<Sprite *> sprites;
    bool read(std::string filePath);
};