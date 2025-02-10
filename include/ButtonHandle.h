#ifndef BUTTON_HANDLE_H
#define BUTTON_HANDLE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>

class ButtonHandle {
public:
    ButtonHandle();
    void addButton(sf::Keyboard::Key key, std::function<void()> onClick);
    void handleEvent(const sf::Event& event);

private:
    std::unordered_map<sf::Keyboard::Key, std::function<void()>> buttonActions;
};

#endif // BUTTON_HANDLE_H
