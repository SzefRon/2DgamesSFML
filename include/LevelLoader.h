#pragma once

#include <fstream>
#include <sstream>
#include <rapidjson/document.h>
#include <iostream>
#include <string>
#include <deque>
#include <SFML/Graphics.hpp>

#include "Sprite.h"

class LevelLoader
{
private:
    rapidjson::Document document;
public:
    std::deque<Sprite *> sprites;
    bool read(std::string filePath);
};