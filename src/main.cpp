#include "Game.h"
#include "LevelCreator.h"

#include <iostream>
#include <cstdlib>

int main()
{
    // std::map<sf::Vector3i, lc::Block, Vector3iComparator> blockMap;
    // blockMap.insert({sf::Vector3i(0, 0, 0), lc::Block("cobble", "square", "stone.png")});
    // LevelCreator::createLevelBMP(".\\res\\levels\\mazes\\maze2.json", "G:\\VSCode\\2DgamesSFML\\res\\levels\\mazes\\maze2.bmp", blockMap, sf::Vector2i(0, 0));
    
    srand(time(nullptr));
    Game game(1280, 720);
    game.start();
}