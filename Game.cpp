
#include "Game.h"
#include "GameState.h"
#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

sf::Texture backgroundTexture; // Define here

void initializeGame(GameState& state, sf::RenderWindow& window, sf::Sprite& backgroundSprite) {
    std::vector<std::string> backgroundFiles = {
        getAssetPath("images/blond_girl.png"),
        getAssetPath("images/claws_girl.png"),
        getAssetPath("images/fantasy_girl.png"),
        getAssetPath("images/fire_girl.png"),
        getAssetPath("images/skul_girl.png"),
        getAssetPath("images/sofa_girl.png")
    };

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, backgroundFiles.size() - 1);
    int index = dis(g);

    std::cout << "[Debug] Loading background texture: " << backgroundFiles[index] << std::endl;
    if (!backgroundTexture.loadFromFile(backgroundFiles[index])) {
        std::cerr << "Failed to load background texture: " << backgroundFiles[index] << std::endl;
        throw std::runtime_error("Failed to load background texture");
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Adjust the sprite to maintain aspect ratio and cover the window
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x);
    float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y);

    // Choose the larger scale to ensure the background covers the entire window
    float scale = std::max(scaleX, scaleY);
    backgroundSprite.setScale(scale, scale);

    // Center the sprite in the window
    backgroundSprite.setPosition(
        (windowSize.x - static_cast<float>(textureSize.x) * scale) / 2,
        (windowSize.y - static_cast<float>(textureSize.y) * scale) / 2
    );

    std::cout << "[Debug] Background texture loaded successfully and resized" << std::endl;

    state.canBet = true;
    state.gameStarted = false;
    state.mainGameHand.clear();
    state.drawFiveCards = false;
}









void initializeUIElements(GameState& state, sf::RenderWindow& window) {
    state.creditsText = std::make_unique<sf::Text>();
    state.betText = std::make_unique<sf::Text>();
    state.instructions = std::make_unique<sf::Text>();
}

void updateUI(sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& instructions, sf::Text& creditsLabelText, sf::Text& creditsValueText, sf::Text& betLabelText, sf::Text& betValueText, std::vector<std::unique_ptr<sf::Text>>& prizeTexts, std::vector<Card>& hand, bool gameOver, sf::Text& gameOverText, int playerCredits, int betAmount, int prize) {
    window.draw(backgroundSprite);
    window.draw(instructions);
    window.draw(creditsLabelText);
    window.draw(creditsValueText);
    window.draw(betLabelText);
    window.draw(betValueText);
    for (const auto& prizeText : prizeTexts) {
        window.draw(*prizeText); // Dereference unique_ptr
    }
    for (const auto& card : hand) {
        window.draw(*card.sprite); // Dereference unique_ptr to draw the sprite
    }
    if (gameOver) {
        window.draw(gameOverText);
    }
}

void handleButtonInputs(const sf::Event& event, std::vector<Card>& hand, bool& canBet, int& betAmount, bool& canCollect, int& prize, int& playerCredits, bool& drawFiveCards, bool& roundInProgress, GameState& state, sf::RenderWindow& window, sf::Text& creditsText, sf::Text& betText, std::vector<std::unique_ptr<sf::Text>>& prizeTexts, sf::Sound& prizeSound, const sf::Font& font, const std::map<std::string, int>& prizeMultipliers) {
    // Implementation of handleButtonInputs
}

void startGame(GameState& state, Deck& deck, SoundManager& soundManager) {
    // Implementation of startGame
}
