#include "Game.h"
#include "GameState.h"
#include "Deck.h"
#include "Card.h"
#include "SoundManager.h"

Game::Game() : window(nullptr) {}

void Game::initialize(sf::RenderWindow& window, GameState& state) {
    this->window = &window;
    // Initialize other game state and UI elements
}

void Game::run(GameState& state) {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            handleButtonInputs(event, state);
        }
        // Update and render game state
    }
}

sf::Sprite& Game::getBackgroundSprite() {
    return backgroundSprite;
}

std::vector<Card> Game::createDeck() {
    std::vector<Card> deck;
    const char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const char suits[] = {'H', 'D', 'C', 'S'};

    for (char suit : suits) {
        for (char rank : ranks) {
            Card card(rank, suit);
            std::string filePath = getAssetPath("cards/" + std::string(1, rank) + std::string(1, suit) + ".png");
            if (loadTexture(card, filePath)) {
                deck.push_back(card);
            }
        }
    }
    return deck;
}

void Game::shuffleDeck(std::vector<Card>& deck) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

// Implement other methods for Game class as needed

