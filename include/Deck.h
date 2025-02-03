#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck {
public:
    Deck() = default; // Default constructor
    void createDeck();
    void shuffleDeck();
    std::vector<Card>& getCards(); // Method to retrieve cards

private:
    std::vector<Card> cards; // Store cards
};

#endif // DECK_H
