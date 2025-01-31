#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>
#include <random>
#include "Card.h"

class Deck {
public:
    Deck();
    void shuffle();
    Card dealCard();
    bool isEmpty() const;
    void createDeck(); // Make this method public

private:
    std::vector<Card> cards;
};

#endif // DECK_H
