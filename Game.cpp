#include "Game.h"
#include <iostream>
#include <filesystem>

const std::string ASSET_DIR = "D:/Projects/softypoker/";

Game::Game()
    : betAmount(1), canBet(true), gameOver(false), gameStarted(false), drawFiveCards(false), prize(0), playerCredits(10),
      prizeMultipliers({{"Super Royal", 336}, {"Royal Flush", 198}, {"Straight Flush", 134}, {"Four of a Kind", 72},
                        {"Full House", 36}, {"Flush", 19}, {"Straight", 11}, {"Three of a Kind", 7}, {"Two Pair", 3},
                        {"Jacks or Better", 1}}) {}

void Game::initialize(sf::RenderWindow& window) {
    this->window = &window;
    view = sf::View(sf::FloatRect(0, 0, 1280, 720));
    window.setView(view);

    if (!font.loadFromFile(ASSET_DIR + "fonts/arialnbi.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        exit(-1);
    }

    try {
        soundManager.initializeAllSounds();
        soundManager.playRandomBackgroundMusic();
    } catch (const std::exception& e) {
        std::cerr << "Sound initialization error: " << e.what() << std::endl;
        exit(-1);
    }

    initializeUIElements();
}

void Game::run() {
    sf::Clock clock;
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::Resized) {
                handleResize(event.size.width, event.size.height);
            } else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                handleButtonInputs(event);
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Rendering
        window->clear();
        window->draw(backgroundSprite);
        window->draw(*creditsText);
        window->draw(*betText);
        window->draw(*instructions);
        window->draw(*gameOverText);
        for (const auto& prizeText : prizeTexts) {
            window->draw(*prizeText);
        }
        window->display();
    }
}

void Game::initializeUIElements() {
    const int characterSize = 24;
    const sf::Color labelColor = sf::Color::Blue;
    const sf::Color valueColor = sf::Color::Green;

    auto initializeText = [&](std::unique_ptr<sf::Text>& text, const std::string& str, int size, const sf::Color& color) {
        text = std::make_unique<sf::Text>();
        text->setFont(font);
        text->setCharacterSize(size);
        text->setFillColor(color);
        text->setString(str);
    };

    initializeText(betText, "Bet: 1", characterSize, valueColor);
    initializeText(creditsText, "Credits: 10", characterSize, valueColor);
    initializeText(gameOverText, "0-INIT", 60, sf::Color(144, 238, 144));
    gameOverText->setPosition(window->getSize().x * 0.70f, window->getSize().y * 0.50f + 40);

    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    betText->setPosition(windowWidth * 0.05f, windowHeight * 0.1f);
    creditsText->setPosition(windowWidth * 0.2f, windowHeight * 0.1f);
}

// Implement other methods (handleResize, handleButtonInputs, handleStartGame, handleBetIncrease, handleDealCards, handleCollectPrize, updatePrizeTexts, updateCardPositionsAndScales)