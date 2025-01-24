#ifndef BUTTONINPUTCONTEXT_H
#define BUTTONINPUTCONTEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Card.h"
#include "SoundManager.h"

struct ButtonInputContext {
    const sf::Event& event;
    std::vector<Card>& hand;
    bool& canBet;
    int& betAmount;
    bool& canCollect;
    int& prize;
    int& playerCredits;
    bool& drawFiveCards;
    bool& roundInProgress;
    bool& gameOver;
    std::vector<Card>& deck;
    sf::RenderWindow& window;
    sf::Sprite& backgroundSprite;
    sf::Text& creditsText;
    sf::Text& betText;
    bool& gameStarted;
    std::vector<sf::Text>& prizeTexts;
    const sf::Font& font;
    sf::Sound& cardDealSound;
    sf::Sound& heldSound;
    sf::Sound& unheldSound;
    sf::Sound& countSound;
    sf::Text& instructions;
    sf::Text& gameOverText;
    bool& gamblingPhase;
    SoundManager& soundManager;
    sf::Text& creditsLabelText;
    sf::Text& creditsValueText;
    sf::Text& betLabelText;
    sf::Text& betValueText;
    sf::Text& prizeValueOnlyText;
    std::map<std::string, int>& prizeMultipliers;
};

#endif // BUTTONINPUTCONTEXT_H
