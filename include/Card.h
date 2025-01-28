#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include <map>

class Card {
public:
    char rank;
    char suit;
    std::unique_ptr<sf::Sprite> sprite;  // Use a smart pointer
    std::unique_ptr<sf::Texture> texture;  // Use a smart pointer
    bool isHeld;

    // Constructor
    Card() : rank(' '), suit(' '), isHeld(false) {
        sprite = std::make_unique<sf::Sprite>();
        texture = std::make_unique<sf::Texture>();
    }

    // Method to get rank as an integer
    int getRankAsInt() const {
        static std::map<char, int> rankToValue = {
            {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
            {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}
        };
        auto it = rankToValue.find(rank);
        return (it != rankToValue.end()) ? it->second : -1;
    }

    // Method to set texture and update sprite
    void setTexture(const sf::Texture& tex) {
        *texture = tex;
        sprite->setTexture(*texture);
    }
};

#endif // CARD_H
