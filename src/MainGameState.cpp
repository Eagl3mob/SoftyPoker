#include "MainGameState.h"
#include <SFML/Graphics.hpp>

namespace SoftyPoker {

MainGameState::MainGameState(SoundManager& sp, sf::RenderWindow& window, const std::string& backgroundPath)
    : soundPlayer(sp) {
    // Initialize ButtonHandle and add button functionalities
    buttonHandle.addButton(sf::Keyboard::S, [this]() { startGame(); });
    buttonHandle.addButton(sf::Keyboard::B, [this]() { bet(); });
    buttonHandle.addButton(sf::Keyboard::D, [this]() { deal(); });
    buttonHandle.addButton(sf::Keyboard::C, [this]() { collect(); });
    buttonHandle.addButton(sf::Keyboard::G, [this]() { enterGamblingState(); });
    buttonHandle.addButton(sf::Keyboard::Left, [this]() { guessSmall(); });
    buttonHandle.addButton(sf::Keyboard::Right, [this]() { guessHigh(); });

    // Initialize separate buttons for holding cards
    buttonHandle.addButton(sf::Keyboard::Num1, [this]() { holdCard(1); });
    buttonHandle.addButton(sf::Keyboard::Num2, [this]() { holdCard(2); });
    buttonHandle.addButton(sf::Keyboard::Num3, [this]() { holdCard(3); });
    buttonHandle.addButton(sf::Keyboard::Num4, [this]() { holdCard(4); });
    buttonHandle.addButton(sf::Keyboard::Num5, [this]() { holdCard(5); });

    // Load background texture
    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        throw std::runtime_error("Failed to load background texture: " + backgroundPath);
    }
    backgroundSprite.setTexture(backgroundTexture);
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
    buttonHandle.handleEvent(event);
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    // Handle other events
}

void MainGameState::startGame() { /* Start game logic */ }
void MainGameState::bet() { /* Betting logic */ }
void MainGameState::deal() { /* Dealing cards logic */ }
void MainGameState::collect() { /* Collect winnings logic */ }
void MainGameState::enterGamblingState() { /* Enter gambling state logic */ }
void MainGameState::guessSmall() { /* Guess small logic */ }
void MainGameState::guessHigh() { /* Guess high logic */ }
void MainGameState::holdCard(int cardIndex) { /* Hold card logic */ }

} // namespace SoftyPoker

