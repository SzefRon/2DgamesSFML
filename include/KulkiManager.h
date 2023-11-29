#pragma once

#include <vector>
#include <random>
#include <iostream>

#include "Kulka.h"

class KulkiManager
{
private:
    int windowX, windowY;
    std::vector<Kulka *> kulki;
    void manageCollision(Kulka *checkKulka, std::map<sf::Keyboard::Scan::Scancode, bool> &keyboardToggles);
public:
    KulkiManager(int iloscKulek, int initSizeX, int initSizeY);
    void draw(sf::RenderWindow *window);
    void update(std::map<sf::Keyboard::Scan::Scancode, bool> &keyboardToggles,
        sf::Vector2f cameraPos, sf::Vector2f cameraSize, sf::Time dt);
};