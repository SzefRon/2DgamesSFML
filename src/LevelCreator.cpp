#include "LevelCreator.h"

void LevelCreator::createLevelBMP(std::string levelPath, std::string bmpPath, std::map<sf::Vector3i, lc::Block, Vector3iComparator> &blockMap, sf::Vector2i offset)
{
    
    rapidjson::Document d;
    d.SetObject();
    auto &allocator = d.GetAllocator();

    rapidjson::Value palette(rapidjson::kArrayType);

    for (auto &map : blockMap) {
        auto &block = map.second;

        rapidjson::Value paletteBlock;
        paletteBlock.SetObject();
        paletteBlock.AddMember("name", rapidjson::Value(block.name.c_str(), block.name.length()).Move(), allocator);
        paletteBlock.AddMember("type", rapidjson::Value(block.type.c_str(), block.type.length()).Move(), allocator);
        paletteBlock.AddMember("texture", rapidjson::Value(block.texture.c_str(), block.texture.length()).Move(), allocator);

        palette.PushBack(paletteBlock.Move(), allocator);
    }
    d.AddMember("palette", palette, allocator);

    rapidjson::Value level(rapidjson::kArrayType);

    BMP image;
    image.ReadFromFile(bmpPath.c_str());

    for (int i = 0; i < image.TellWidth(); i++) {
        for (int j = 0; j < image.TellHeight(); j++) {
            RGBApixel pixel = image.GetPixel(i, j);
            sf::Vector3i pixelV(pixel.Red, pixel.Green, pixel.Blue);

            if (blockMap.find(pixelV) != blockMap.end()) {
                lc::Block &block = blockMap[pixelV];

                rapidjson::Value levelBlock;
                levelBlock.SetObject();

                levelBlock.AddMember("name", rapidjson::Value(block.name.c_str(), block.name.length()).Move(), allocator);

                rapidjson::Value pos(rapidjson::kArrayType);
                pos.PushBack(rapidjson::Value(i + offset.x).Move(), allocator);
                pos.PushBack(rapidjson::Value(j + offset.y).Move(), allocator);

                levelBlock.AddMember("pos", pos.Move(), allocator);
                levelBlock.AddMember("rotation", rapidjson::Value(0).Move(), allocator);

                level.PushBack(levelBlock, allocator);
            }
        }
    }

    d.AddMember("level", level, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    const char *output = buffer.GetString();
    std::ofstream file(levelPath);
    file << output;
    file.close();
}