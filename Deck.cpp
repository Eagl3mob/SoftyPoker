#include "Deck.h"

Deck::Deck() {
    createDeck();
    shuffle();
}

void Deck::createDeck() {
    cards.clear();
    const char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const char suits[] = {'H', 'D', 'C', 'S'};
    for (char suit : suits) {
        for (char rank : ranks) {
            Card card;
            card.suit = suit;
            card.rank = rank;
            cards.push_back(card);
        }
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::dealCard() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

bool Deck::isEmpty() const {
    return cards.empty();
}


