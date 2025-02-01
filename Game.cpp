#include "Game.h"
#include "GameState.h"
#include "Deck.h"
#include "Card.h"
#include "SoundManager.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>

// Constructor
Game::Game() {
    // Initialization code here
}

// Get background sprite
sf::Sprite& Game::getBackgroundSprite() {
    return backgroundSprite;
}

// Run the game
void Game::run(GameState& state) {
    // Game loop code here
}

// Shuffle the deck
void Game::shuffleDeck(std::vector<Card>& deck) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

// Create the deck
std::vector<Card> Game::createDeck() {
    std::vector<Card> deck;
    const char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const char suits[] = {'H', 'D', 'C', 'S'};

    for (char suit : suits) {
        for (char rank : ranks) {
            Card card;
            card.suit = suit;
            card.rank = rank;
            std::string filePath = getAssetPath("cards/" + std::string(1, rank) + std::string(1, suit) + ".png");
            if (loadTexture(card, filePath)) {
                deck.push_back(std::move(card)); // Use std::move to move the card
            }
        }
    }
    return deck;
}
