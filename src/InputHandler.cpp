#include "InputHandler.h"

InputHandler::InputHandler(sf::RenderWindow *window)
{
    this->window = window;
    window->setKeyRepeatEnabled(false);
    keyboardInputs.emplace(sf::Keyboard::Scan::Scancode::Up, false);
    keyboardInputs.emplace(sf::Keyboard::Scan::Scancode::Down, false);
    keyboardInputs.emplace(sf::Keyboard::Scan::Scancode::Left, false);
    keyboardInputs.emplace(sf::Keyboard::Scan::Scancode::Right, false);
    keyboardInputs.emplace(sf::Keyboard::Scan::Scancode::W, false);
    keyboardInputs.emplace(sf::Keyboard::Scan::Scancode::A, false);
    keyboardInputs.emplace(sf::Keyboard::Scan::Scancode::S, false);
    keyboardInputs.emplace(sf::Keyboard::Scan::Scancode::D, false);

    keyboardPresses.emplace(sf::Keyboard::Scan::Scancode::Up, false);
    keyboardPresses.emplace(sf::Keyboard::Scan::Scancode::W, false);
    keyboardPresses.emplace(sf::Keyboard::Scan::Scancode::Q, false);
    keyboardPresses.emplace(sf::Keyboard::Scan::Scancode::E, false);
    keyboardPresses.emplace(sf::Keyboard::Scan::Scancode::Z, false);
    keyboardPresses.emplace(sf::Keyboard::Scan::Scancode::C, false);

    keyboardReleases.emplace(sf::Keyboard::Scan::Scancode::Up, false);
    keyboardReleases.emplace(sf::Keyboard::Scan::Scancode::W, false);
}

void InputHandler::handleEvents()
{
    for (auto &presses : keyboardPresses) {
        presses.second = false;
    }
    for (auto &releases : keyboardReleases) {
        releases.second = false;
    }
    for (auto event = sf::Event{}; window->pollEvent(event);) {
        if (event.type == sf::Event::KeyPressed) {
            if (auto found = keyboardInputs.find(event.key.scancode); found != keyboardInputs.end()) {
                found->second = true;
            }
            if (auto found = keyboardPresses.find(event.key.scancode); found != keyboardPresses.end()) {
                found->second = true;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (auto found = keyboardInputs.find(event.key.scancode); found != keyboardInputs.end()) {
                found->second = false;
            }
            if (auto found = keyboardReleases.find(event.key.scancode); found != keyboardReleases.end()) {
                found->second = true;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (auto found = mouseInputs.find(event.mouseButton.button); found != mouseInputs.end()) {
                found->second = true;
                //std::cout << "Mouse pressed: " << found->first << '\n';
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (auto found = mouseInputs.find(event.mouseButton.button); found != mouseInputs.end()) {
                found->second = false;
                //std::cout << "Mouse released: " << found->first << '\n';
            }
        }
        if (event.type == sf::Event::MouseMoved) {
            mousePos.first = event.mouseMove.x;
            mousePos.second = event.mouseMove.y;
            //std::cout << "Mouse moved to: " << mousePos.first << ", " << mousePos.second << '\n';
        }
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}