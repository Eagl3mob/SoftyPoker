#include "GameState.h"

GameState::GameState()
    : canBet(true), gameOver(false), gameStarted(false), drawFiveCards(true), betAmount(1) {
    // Initialize prize multipliers
    prizeMultipliers = {
        {"Super Royal", 336}, {"Royal Flush", 198}, {"Straight Flush", 134},
        {"Four of a Kind", 72}, {"Full House", 36}, {"Flush", 19},
        {"Straight", 11}, {"Three of a Kind", 7}, {"Two Pair", 3}, {"Jacks or Better", 1}
    };
}
