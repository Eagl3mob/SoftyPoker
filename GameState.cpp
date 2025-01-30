#include "GameState.h"

GameState::GameState()
    : betAmount(1), canBet(true), gameOver(false), gameStarted(false), drawFiveCards(false),
      prizeMultipliers({{"Super Royal", 336}, {"Royal Flush", 198}, {"Straight Flush", 134},
                        {"Four of a Kind", 72}, {"Full House", 36}, {"Flush", 19},
                        {"Straight", 11}, {"Three of a Kind", 7}, {"Two Pair", 3}, {"Jacks or Better", 1}}) {
    // Initialize text objects
    instructions = std::make_unique<sf::Text>();
    creditsText = std::make_unique<sf::Text>();
    betText = std::make_unique<sf::Text>();
    gameOverText = std::make_unique<sf::Text>();
}
