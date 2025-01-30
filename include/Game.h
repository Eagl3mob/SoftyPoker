#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include <memory>
#include "Card.h"
#include "Deck.h"
#include "SoundManager.h"

class Game {
public:
    Game();
    void initialize(sf::RenderWindow& window);
    void run();

private:
    void initializeUIElements();
    void handleResize(int newWidth, int newHeight);
    void handleButtonInputs(const sf::Event& event);
    void handleStartGame();
    void handleBetIncrease();
    void handleDealCards();
    void handleCollectPrize();
    void updatePrizeTexts();
    void updateCardPositionsAndScales();

    sf::RenderWindow* window;
    sf::View view;
    sf::Font font;
    std::unique_ptr<sf::Text> instructions;
    std::unique_ptr<sf::Text> creditsText;
    std::unique_ptr<sf::Text> betText;
    std::unique_ptr<sf::Text> gameOverText;
    std::vector<std::unique_ptr<sf::Text>> prizeTexts;
    sf::Sprite backgroundSprite;
    SoundManager soundManager;

    int betAmount;
    bool canBet;
    bool gameOver;
    bool gameStarted;
    std::vector<Card> mainGameHand;
    bool drawFiveCards;
    int prize;
    int playerCredits;
    std::map<std::string, int> prizeMultipliers;

    sf::SoundBuffer cardDealBuffer;
    sf::SoundBuffer heldBuffer;
    sf::SoundBuffer unheldBuffer;
};

#endif // GAME_H

