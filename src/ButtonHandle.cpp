#include "ButtonHandle.h"

ButtonHandle::ButtonHandle() {}

void ButtonHandle::addButton(sf::Keyboard::Key key, std::function<void()> onClick) {
    buttonActions[key] = onClick;
}

void ButtonHandle::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        auto it = buttonActions.find(event.key.code);
        if (it != buttonActions.end()) {
            it->second();
        }
    }
}
