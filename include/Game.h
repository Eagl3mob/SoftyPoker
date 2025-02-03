#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "SoundManager.h"
#include "GameState.h"

extern sf::Texture backgroundTexture;

// Function declarations
void initializeGame(GameState& state, sf::RenderWindow& window, sf::Sprite& backgroundSprite);
void initializeUIElements(GameState& state, sf::RenderWindow& window);
void updateUI(sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& instructions, sf::Text& creditsLabelText, sf::Text& creditsValueText, sf::Text& betLabelText, sf::Text& betValueText, std::vector<std::unique_ptr<sf::Text>>& prizeTexts, std::vector<Card>& hand, bool gameOver, sf::Text& gameOverText, int playerCredits, int betAmount, int prize);
void handleButtonInputs(const sf::Event& event, std::vector<Card>& hand, bool& canBet, int& betAmount, bool& canCollect, int& prize, int& playerCredits, bool& drawFiveCards, bool& roundInProgress, GameState& state, sf::RenderWindow& window, sf::Text& creditsText, sf::Text& betText, std::vector<std::unique_ptr<sf::Text>>& prizeTexts, sf::Sound& prizeSound, const sf::Font& font, const std::map<std::string, int>& prizeMultipliers);
void startGame(GameState& state, Deck& deck, SoundManager& soundManager);

#endif // GAME_H
