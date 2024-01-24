#include "Background.h"

Background::Background(float speed, float xOffset, float yPos, int count, sf::Sprite *sprite)
    : speed(speed), xOffset(xOffset), yPos(yPos), count(count)
{
    float sizeX = sprite->getScale().x * sprite->getTexture()->getSize().x;
    for (int i = 0; i < count; i++) {
        int x = (sizeX + xOffset) * (i - 10);
        std::cout << x << '\n';
        sf::Sprite *newSprite = new sf::Sprite(*sprite);
        newSprite->setPosition(sf::Vector2f(x, yPos));
        this->sprites.push_back(newSprite);
    }
}

void Background::update(sf::Vector2f cameraOffset)
{
    for (int i = 0; i < count; i++) {
        sprites[i]->setPosition(sprites[i]->getPosition() - sf::Vector2f(speed * cameraOffset.x, 0));
    }
}
