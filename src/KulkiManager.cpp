#include "KulkiManager.h"

#include "Maths.h"

void KulkiManager::manageCollision(Kulka *checkKulka, std::map<sf::Keyboard::Scan::Scancode, bool> &keyboardToggles)
{
    for (auto &kulka : kulki) {
        if (kulka == checkKulka) continue;
        float dist = std::sqrtf((kulka->x - checkKulka->x) * (kulka->x - checkKulka->x) + (kulka->y - checkKulka->y) * (kulka->y - checkKulka->y));
        if (dist < 128.0f) {
            float dx = ((checkKulka->x - kulka->x) / dist) * (128.0f - dist);
            float dy = ((checkKulka->y - kulka->y) / dist) * (128.0f - dist);
            
            if (keyboardToggles[sf::Keyboard::Scan::Scancode::E]) checkKulka->move(dx, dy);

            float len = std::sqrtf(dx * dx + dy * dy);
            float ndx = dx / len;
            float ndy = dy / len;

            float dot1 = ndx * checkKulka->vx + ndy * checkKulka->vy;
            float newvx1 = checkKulka->vx - 2.0f * dot1 * ndx;
            float newvy1 = checkKulka->vy - 2.0f * dot1 * ndy;

            if (keyboardToggles[sf::Keyboard::Scan::Scancode::R]) {
                checkKulka->vx = newvx1;
                checkKulka->vy = newvy1;
            }
        }
    }
}

KulkiManager::KulkiManager(int iloscKulek, int initSizeX, int initSizeY)
    : windowX(initSizeX), windowY(initSizeY)
{
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("..\\..\\res\\textures\\ball.png");
    Kulka *kulka;

    for (int i = 0; i < iloscKulek; i++) {
        float x = Maths::randFloat(0.0f, initSizeX);
        float y = Maths::randFloat(0.0f, initSizeY);
        float vx = Maths::randFloat(-0.5f, 0.5f);
        float vy = Maths::randFloat(-0.5f, 0.5f);
        kulka = new Kulka(*texture, x, y, vx, vy);
        kulki.push_back(kulka);
    }
}

void KulkiManager::draw(sf::RenderWindow *window)
{
    for (auto &kulka : kulki) {
        window->draw(*(kulka->sprite));
    }
}

void KulkiManager::update(std::map<sf::Keyboard::Scan::Scancode, bool> &keyboardToggles, 
    sf::Vector2f cameraPos, sf::Vector2f cameraSize, sf::Time dt)
{
    int dtMilli = dt.asMilliseconds();
    for (auto &kulka : kulki) {
        kulka->move(kulka->vx * dtMilli, kulka->vy * dtMilli);
        manageCollision(kulka, keyboardToggles);
        if ((kulka->x + 64.0f) >= cameraPos.x + cameraSize.x * 0.5f) {
            kulka->vx *= -1.0f;
            float separationX = (cameraPos.x + cameraSize.x * 0.5f - (kulka->x + 64.0f));
            kulka->move(separationX, 0.0f);
        }
        if ((kulka->x - 64.0f) <= cameraPos.x - cameraSize.x * 0.5f) {
            kulka->vx *= -1.0f;
            float separationX = (cameraPos.x - cameraSize.x * 0.5f - (kulka->x - 64.0f));
            kulka->move(separationX, 0.0f);
        }
        if ((kulka->y + 64.0f) >= cameraPos.y + cameraSize.y * 0.5f) {
            kulka->vy *= -1.0f;
            float separationY = (cameraPos.y + cameraSize.y * 0.5f - (kulka->y + 64.0f));
            kulka->move(0.0f, separationY);
        }
        if ((kulka->y - 64.0f) <= cameraPos.y - cameraSize.y * 0.5f) {
            kulka->vy *= -1.0f;
            float separationY = (cameraPos.y - cameraSize.y * 0.5f - (kulka->y - 64.0f));
            kulka->move(0.0f, separationY);
        }
    }
}
