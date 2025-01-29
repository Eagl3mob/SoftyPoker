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

private:
    std::vector<Card> cards;
    void createDeck();
};

#endif // DECK_H

