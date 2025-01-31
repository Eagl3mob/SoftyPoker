
#include "Game.h"
#include <iostream>
#include <filesystem>

const std::string ASSET_DIR = "D:/Projects/softypoker/";

Game::Game() {}

void Game::initialize(sf::RenderWindow& window, GameState& state) {
    this->window = &window;
    view = sf::View(sf::FloatRect(0, 0, 1280, 720));
    window.setView(view);

    if (!state.font.loadFromFile(getAssetPath("fonts/arialnbi.ttf"))) {
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

    initializeUIElements(state);
}







std::vector<Card> Game::createDeck() {
    std::vector<Card> deck;
    const char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const char suits[] = {'H', 'D', 'C', 'S'};

    for (char suit : suits) {
        for (char rank : ranks) {
            Card card;
            card.suit = suit;
            card.rank = rank;
            std::string filePath = getAssetPath("cards/" + std::string(1, rank) + std::string(1, suit) + ".png");
            if (loadTexture(card, filePath)) {
                deck.push_back(card);
            }
        }
    }
    return deck;
}






void Game::run(GameState& state) {
    sf::Clock clock;
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::Resized) {
                handleResize(event.size.width, event.size.height, state);
            } else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                handleButtonInputs(event, state);
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Rendering
        window->clear();
        window->draw(backgroundSprite);
        window->draw(*state.creditsText);
        window->draw(*state.betText);
        window->draw(*state.instructions);
        window->draw(*state.gameOverText);
        for (const auto& prizeText : state.prizeTexts) {
            window->draw(*prizeText);
        }
        window->display();
    }
}

void Game::initializeUIElements(GameState& state) {
    const int characterSize = 24;
    const sf::Color labelColor = sf::Color::Blue;
    const sf::Color valueColor = sf::Color::Green;

    auto initializeText = [&](std::unique_ptr<sf::Text>& text, const std::string& str, int size, const sf::Color& color) {
        text = std::make_unique<sf::Text>();
        text->setFont(state.font);
        text->setCharacterSize(size);
        text->setFillColor(color);
        text->setString(str);
    };

    initializeText(state.betText, "Bet: 1", characterSize, valueColor);
    initializeText(state.creditsText, "Credits: 10", characterSize, valueColor);
    initializeText(state.gameOverText, "0-INIT", 60, sf::Color(144, 238, 144));
    state.gameOverText->setPosition(window->getSize().x * 0.70f, window->getSize().y * 0.50f + 40);

    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    state.betText->setPosition(windowWidth * 0.05f, windowHeight * 0.1f);
    state.creditsText->setPosition(windowWidth * 0.2f, windowHeight * 0.1f);
}

// Implement other methods (handleResize, handleButtonInputs, handleStartGame, handleBetIncrease, handleDealCards, handleCollectPrize, updatePrizeTexts, updateCardPositionsAndScales)
