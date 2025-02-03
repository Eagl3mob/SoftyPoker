#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "Card.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <map>

class GameState {
public:
    GameState(); // Declare the constructor

    bool canBet;
    bool gameOver;
    bool gameStarted;
    bool drawFiveCards;
    int betAmount;
    std::vector<Card> mainGameHand;
    std::vector<std::unique_ptr<sf::Text>> prizeTexts;
    std::unique_ptr<sf::Text> instructions;
    std::unique_ptr<sf::Text> creditsText;
    std::unique_ptr<sf::Text> betText;
    std::unique_ptr<sf::Text> gameOverText;
    sf::Font font;
    std::map<std::string, int> prizeMultipliers; // Add the prize multipliers field
};

#endif // GAMESTATE_H
