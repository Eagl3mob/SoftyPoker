#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <memory>
#include "Card.h"

class GameState {
public:
    GameState();
    
    sf::Font font;
    std::unique_ptr<sf::Text> instructions;
    std::unique_ptr<sf::Text> creditsText;
    std::unique_ptr<sf::Text> betText;
    std::unique_ptr<sf::Text> gameOverText;
    std::vector<std::unique_ptr<sf::Text>> prizeTexts;

    int betAmount;
    bool canBet;
    bool gameOver;
    bool gameStarted;
    std::vector<Card> mainGameHand;
    bool drawFiveCards;
    sf::SoundBuffer cardDealBuffer;
    sf::SoundBuffer heldBuffer;
    sf::SoundBuffer unheldBuffer;

    std::map<std::string, int> prizeMultipliers;
};

#endif // GAMESTATE_H
