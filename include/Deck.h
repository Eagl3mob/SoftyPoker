#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

std::vector<Card> createDeck();  // Declaration
void shuffleDeck(std::vector<Card>& deck);
#endif // DECK_H
