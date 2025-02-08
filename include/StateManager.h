#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "GameState.h"
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

class StateManager {
private:
    std::unordered_map<std::string, std::unique_ptr<GameState>> states;
    GameState* currentState = nullptr;

public:
    StateManager() = default;
    ~StateManager() = default;

    void addState(const std::string& name, std::unique_ptr<GameState> state) {
        states[name] = std::move(state);
    }

    void switchToState(const std::string& name) {
        currentState = states[name].get();
    }

    void update(sf::RenderWindow& window) {
        if (currentState) {
            currentState->update(window);
        }
    }

    void draw(sf::RenderWindow& window) {
        if (currentState) {
            currentState->draw(window);
        }
    }

    void handleEvent(sf::Event& event, sf::RenderWindow& window) {  // Update to match new signature
        if (currentState) {
            currentState->handleEvent(event, window);
        }
    }
};

#endif // STATEMANAGER_H
