#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>

struct Card {
    sf::Sprite sprite;
    sf::Texture* texture;
    char suit;
    char rank;
    bool isHeld = false;

    int getRankAsInt() const {
        if (rank == 'A') return 14;
        if (rank == 'K') return 13;
        if (rank == 'Q') return 12;
        if (rank == 'J') return 11;
        if (rank == 'T') return 10;
        return rank - '0'; // Converts '2' to 2, '3' to 3, etc.
    }
};

bool loadTexture(Card& card, const std::string& filePath);

#endif // CARD_H
