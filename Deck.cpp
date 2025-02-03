#include "Deck.h"
#include <algorithm>
#include <random>

void Deck::createDeck() {
    // Clear any existing cards
    cards.clear();

    // Add code to populate the deck with cards
    // Example: adding 52 standard playing cards
    for (char suit : {'H', 'D', 'C', 'S'}) { // Hearts, Diamonds, Clubs, Spades
        for (char rank : {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'}) {
            cards.emplace_back(rank, suit);
        }
    }
}

void Deck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

std::vector<Card>& Deck::getCards() {
    return cards;
}
