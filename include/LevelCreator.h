#pragma once

#include <EasyBMP.h>
#include <map>
#include <SFML/Graphics.hpp>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <fstream>

struct Vector3iComparator
{
    bool operator()(const sf::Vector3i& lhs, const sf::Vector3i& rhs) const {
        if (lhs.x != rhs.x) return lhs.x < rhs.x;
        if (lhs.y != rhs.y) return lhs.y < rhs.y;
        return lhs.z < rhs.z;
    }
};

namespace lc
{
    struct Block
    {
        std::string name;
        std::string type;
        std::string texture;

        Block(std::string name, std::string type, std::string texture)
            : name(name), type(type), texture(texture) {}
        Block() {}
    };
}

class LevelCreator
{
public:
    static void createLevelBMP(std::string levelPath, std::string bmpPath, std::map<sf::Vector3i, lc::Block, Vector3iComparator> &blockMap, sf::Vector2i offset = sf::Vector2i(0, 0));
};