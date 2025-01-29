#include "Deck.h"

const std::string ASSET_DIR = "Assets/";

Deck::Deck() {
    createDeck();
}

void Deck::createDeck() {
    const char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const char suits[] = {'H', 'D', 'C', 'S'};

    for (char suit : suits) {
        for (char rank : ranks) {
            Card card;
            card.suit = suit;
            card.rank = rank;
            std::string filePath = ASSET_DIR + "cards/" + std::string(1, rank) + std::string(1, suit) + ".png";
            if (loadTexture(card, filePath)) {
                cards.push_back(card);
            }
        }
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::dealCard() {
    if (cards.empty()) {
        throw std::out_of_range("No more cards to deal");
    }
    Card dealtCard = cards.back();
    cards.pop_back();
    return dealtCard;
}

bool Deck::isEmpty() const {
    return cards.empty();
}
