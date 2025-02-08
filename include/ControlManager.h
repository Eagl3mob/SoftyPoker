#ifndef CONTROLMANAGER_H
#define CONTROLMANAGER_H

#include "StateManager.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ControlManager {
private:
    StateManager& stateManager;

public:
    ControlManager(StateManager& sm);
    ~ControlManager();

    void handleInput(sf::Event& event, sf::RenderWindow& window);  // Updated declaration
};

#endif // CONTROLMANAGER_H

