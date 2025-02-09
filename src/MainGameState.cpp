#include "MainGameState.h"
#include <SFML/Graphics.hpp>

namespace SoftyPoker {

MainGameState::MainGameState(SoundManager& sp, sf::RenderWindow& window, const std::string& backgroundPath)
    : soundPlayer(sp) {

    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        throw std::runtime_error("Failed to load background texture: " + backgroundPath);
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Initialize main game-specific components
}

void MainGameState::update(sf::RenderWindow& window) {
    sf::Time elapsed = clock.restart();
    // Use elapsed or comment it out if it's not needed
    // Update main game logic
}

void MainGameState::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite); // Draw the background
    // Draw main game elements
    window.display();
}

void MainGameState::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    // Handle main game-specific events
}

} // namespace SoftyPoker


