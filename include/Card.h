#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <map>

class Card {
public:
    char rank;
    char suit;
    std::unique_ptr<sf::Sprite> sprite;
    std::unique_ptr<sf::Texture> texture;
    bool isHeld;

    Card();
    Card(char r, char s);
    Card(const Card& other);
    Card& operator=(const Card& other);
    int getRankAsInt() const;
    void setTexture(const sf::Texture& tex);
};

// Declaration of loadTexture function
bool loadTexture(Card& card, const std::string& filePath);

#endif // CARD_H
