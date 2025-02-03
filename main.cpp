#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include "Game.h"
#include "GameState.h"
#include "Deck.h"
#include "Card.h"
#include "SoundManager.h"
#include "Utility.h"
#include "introState.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SoftyPoker"); // Change resolution here
    GameState state;
    sf::Sprite backgroundSprite;
    Deck deck;
    sf::Sound prizeSound;

    SoundManager soundManager;

    std::cout << "[Debug] Initializing game background" << std::endl;
    initializeGame(state, window, backgroundSprite);

    // Call the introState function to handle the intro screen
    introState(window, soundManager);

    bool roundInProgress = false;
    bool canCollect = false;
    int playerCredits = 100;
    int betAmount = 1;
    int prize = 0;
    bool canBet = true;
    bool drawFiveCards = false;
    bool gameOver = false;

#if ENABLE_UI
    initializeUIElements(state, window);
#endif

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));

                // Adjust the background sprite to maintain aspect ratio and cover the new window size
                sf::Vector2u textureSize = backgroundSprite.getTexture()->getSize();
                float scaleX = static_cast<float>(event.size.width) / static_cast<float>(textureSize.x);
                float scaleY = static_cast<float>(event.size.height) / static_cast<float>(textureSize.y);

                float scale = std::max(scaleX, scaleY);
                backgroundSprite.setScale(scale, scale);
                backgroundSprite.setPosition(
                    (static_cast<float>(event.size.width) - static_cast<float>(textureSize.x) * scale) / 2,
                    (static_cast<float>(event.size.height) - static_cast<float>(textureSize.y) * scale) / 2
                );
            }

#if ENABLE_EVENT_HANDLING
            handleButtonInputs(event, state.mainGameHand, canBet, betAmount, canCollect, prize, playerCredits, drawFiveCards, roundInProgress, state, window, *state.creditsText, *state.betText, state.prizeTexts, prizeSound, state.font, prizeMultipliers);

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                std::cout << "[Debug] Enter pressed, starting game" << std::endl;
                soundManager.initializeGameSounds();
                startGame(state, deck, soundManager);
            }
#endif
        }

#if ENABLE_UI
        updateUI(window, backgroundSprite, *state.instructions, *state.creditsText, *state.betText, *state.betText, *state.betText, state.prizeTexts, state.mainGameHand, gameOver, *state.gameOverText, playerCredits, betAmount, prize);
#endif

        window.clear();
        window.draw(backgroundSprite);
#if ENABLE_UI
        // Draw other game elements here
#endif
        window.display();
    }

    return 0;
}
