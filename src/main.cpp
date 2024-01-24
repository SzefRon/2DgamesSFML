#include "Game.h"
#include "LevelCreator.h"

#include <iostream>
#include <cstdlib>

int main()
{
    // std::map<sf::Vector3i, lc::Block, Vector3iComparator> blockMap;
    // blockMap.insert({sf::Vector3i(0, 0, 0), lc::Block("sidewalk", "square", "sidewalk.png")});
    // blockMap.insert({sf::Vector3i(255, 0, 0), lc::Block("sidewalk_bottom", "square", "sidewalk_bottom.png")});
    // LevelCreator::createLevelBMP(".\\res\\levels\\level3.json", "G:\\VSCode\\2DgamesSFML\\res\\levels\\level3.bmp", blockMap, sf::Vector2i(0, 0));
    
    srand(time(nullptr));
    Game game(1280, 720);
    game.start();
}