#include "StateManager.h"
#include <iostream>

namespace SoftyPoker {

StateManager::StateManager() : currentState(nullptr) {}

void StateManager::addState(const std::string& stateName, std::unique_ptr<GameState> state) {
    states[stateName] = std::move(state);
}

void StateManager::switchToState(const std::string& stateName) {
    if (states.find(stateName) != states.end()) {
        currentState = states[stateName].get();
        currentStateName_ = stateName;
    } else {
        std::cerr << "State " << stateName << " not found!" << std::endl;
    }
}

void StateManager::update(sf::RenderWindow& window) {
    if (currentState) {
        currentState->update(window);
    }
}

void StateManager::draw(sf::RenderWindow& window) {
    if (currentState) {
        currentState->draw(window);
    }
}

void StateManager::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (currentState) {
        currentState->handleEvent(event, window);
    }
}

std::string StateManager::getCurrentStateName() const {
    return currentStateName_;
}

GameState* StateManager::getCurrentState() const {
    return currentState;
}

} // namespace SoftyPoker
