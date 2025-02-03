#include "Card.h"

Card::Card() : rank(' '), suit(' '), isHeld(false) {
    sprite = std::make_unique<sf::Sprite>();
    texture = std::make_unique<sf::Texture>();
}

Card::Card(char r, char s) : rank(r), suit(s), isHeld(false) {
    sprite = std::make_unique<sf::Sprite>();
    texture = std::make_unique<sf::Texture>();
}

Card::Card(const Card& other) : rank(other.rank), suit(other.suit), isHeld(other.isHeld) {
    sprite = std::make_unique<sf::Sprite>(*other.sprite);
    texture = std::make_unique<sf::Texture>(*other.texture);
}

Card& Card::operator=(const Card& other) {
    if (this != &other) {
        rank = other.rank;
        suit = other.suit;
        isHeld = other.isHeld;
        sprite = std::make_unique<sf::Sprite>(*other.sprite);
        texture = std::make_unique<sf::Texture>(*other.texture);
    }
    return *this;
}

int Card::getRankAsInt() const {
    static std::map<char, int> rankToValue = {
        {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
        {'8', 8}, {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}
    };
    auto it = rankToValue.find(rank);
    return (it != rankToValue.end()) ? it->second : -1;
}

void Card::setTexture(const sf::Texture& tex) {
    *texture = tex;
    sprite->setTexture(*texture);
}
