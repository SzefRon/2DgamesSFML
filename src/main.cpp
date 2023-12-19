#include "Game.h"
#include "LevelCreator.h"

#include <iostream>

int main()
{
    // std::map<sf::Vector3i, lc::Block, Vector3iComparator> blockMap;
    // blockMap.insert({sf::Vector3i(0, 0, 0), lc::Block("cobble", "square", "stone.png")});
    // LevelCreator::createLevelBMP(".\\res\\levels\\maze\\maze.json", "G:\\VSCode\\2DgamesSFML\\res\\levels\\maze\\level.bmp", blockMap, sf::Vector2i(-15, -15));

    Game game(1280, 720);
    game.start();
}