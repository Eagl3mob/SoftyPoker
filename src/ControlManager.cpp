#include "ControlManager.h"

ControlManager::ControlManager(StateManager& sm) : stateManager(sm) {
    // Constructor code here (if needed)
}

ControlManager::~ControlManager() {
    // Destructor code here (if needed)
}

void ControlManager::handleInput(sf::Event& event, sf::RenderWindow& window) {  // Match declaration
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    }
    stateManager.handleEvent(event, window);
}
