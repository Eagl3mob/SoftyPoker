
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Card.h"
#include "Deck.h"
#include "SoundManager.h"
#include "ButtonInputContext.h"
//#include "UIHelper.h"
//#include "AnimationHelper.h"
#include <vector>
#include <map>
#include <thread>
#include <random>
#include <iostream>
#include <filesystem>
#include <ctime>
#include <cstdlib>
#include <unordered_set>
#include <memory>


namespace fs = std::filesystem;

// Constants
const float CARD_SCALE_FACTOR = 0.18f;
const float CARD_SPACING = 10.5f;
const float CARD_BOTTOM_OFFSET = 70.0f;
const float CARD_LEFT_OFFSET = 240.0f;

// Global Variables
sf::Font font;
bool gameOver = false;
bool roundInProgress = false;
sf::Text instructions, creditsText, betText, gameOverText;
std::vector<sf::Text> prizeTexts;
int betAmount = 1, playerCredits = 0, prize = 0;
bool canBet = true, gameStarted = false, drawFiveCards = true, gamblingPhase = false, canCollect = false, canHoldCards = true;
std::vector<Card> hand, deck;
sf::Sprite backgroundSprite;
sf::Texture backgroundTexture;
SoundManager soundManager;
bool animateLogoFlag = true;

std::map<std::string, int> prizeMultipliers = {
    {"Super Royal", 336}, {"Royal Flush", 198}, {"Straight Flush", 134},
    {"Four of a Kind", 72}, {"Full House", 36}, {"Flush", 19},
    {"Straight", 11}, {"Three of a Kind", 7}, {"Two Pair", 3}, {"Jacks or Better", 1}
};






// Function declarations
std::vector<Card> createDeck();
bool loadTexture(Card& card, const std::string& filePath);
void shuffleDeck(std::vector<Card>& deck);
void dealInitialHand(std::vector<Card>& deck, std::vector<Card>& hand, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& creditsText, sf::Text& betText, const std::vector<sf::Text>& prizeTexts);
void redrawHand(std::vector<Card>& deck, std::vector<Card>& hand, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& creditsText, sf::Text& betText, const std::vector<sf::Text>& prizeTexts);
void initializeGamblingGame(std::vector<Card>& deck, Card& currentCard);
std::vector<Card> createGamblingDeck();
void updateCardPositionsAndScales(std::vector<Card>& cards, sf::RenderWindow& window);
void updateUI(sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& instructions, sf::Text& creditsLabelText, sf::Text& creditsValueText, sf::Text& betLabelText, sf::Text& betValueText, const std::vector<sf::Text>& prizeTexts, const std::vector<Card>& hand, sf::Text& gameOverText, bool gameOver, int playerCredits, int betAmount);
void initializeAllSounds(sf::Sound& cardDealSound, sf::Sound& heldSound, sf::Sound& unheldSound, sf::Sound& countSound, sf::Sound& loseSound, sf::Sound& winSound);
void drawHeldCardHighlight(sf::RenderWindow& window, const Card& card);
int evaluateHand(const std::vector<Card>& hand, int betAmount);
bool playGamblingRound(std::vector<Card>& deck, Card& currentCard, bool guessHigher, std::unordered_set<int>& usedCards);
void resetGameState(int& playerCredits, int& betAmount, bool& canCollect, bool& drawFiveCards, std::vector<Card>& hand, std::vector<Card>& deck, std::vector<sf::Text>& prizeTexts, const sf::Font& font, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& instructions, sf::Text& creditsLabelText, sf::Text& creditsValueText, sf::Text& betLabelText, sf::Text& betValueText, sf::Text& prizeValueOnlyText, SoundManager& soundManager);
void startGamblingPhase(sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& creditsText, sf::Text& betText, std::vector<sf::Text>& prizeTexts, const sf::Font& font, int& prize, int& playerCredits, sf::Sound& countSound, sf::Sound& loseSound, sf::Sound& winSound, std::vector<Card>& hand, bool& canBet);
void initializePrizeSound(sf::Sound& prizeSound);
float calculateScaleFactor(const sf::RenderWindow& window);
void startGame(sf::RenderWindow& window, const sf::Font& font, std::vector<sf::Text>& prizeTexts, int betAmount, int prize, const std::map<std::string, int>& prizeMultipliers, bool& canBet);
void handleBetPlacement(const sf::Event& event, bool& canBet, int& betAmount, int& playerCredits, std::vector<sf::Text>& prizeTexts, const sf::Font& font, sf::Text& betText, sf::RenderWindow& window, SoundManager& soundManager);
void initializeUIElements(const sf::Font& font, sf::RenderWindow& window, sf::Text& betLabelText, sf::Text& betValueText, sf::Text& creditsLabelText, sf::Text& creditsValueText, sf::Text& prizeValueOnlyText);
void animateLogo(sf::RenderWindow& window, sf::View& view, sf::Sprite& logoSprite, sf::Sprite& backgroundSprite, float speed, sf::Clock& clock);
void handleResize(sf::RenderWindow& window, sf::View& view, sf::Sprite& backgroundSprite, sf::Sprite& logoSprite, int newWidth, int newHeight, SoundManager& soundManager, sf::Text& betLabelText, sf::Text& betValueText, sf::Text& creditsLabelText, sf::Text& creditsValueText, std::vector<sf::Text>& prizeTexts, sf::Text& prizeValueOnlyText, sf::Text& instructions);
void updatePrizeTexts(std::vector<sf::Text>& prizeTexts, int betAmount, const sf::Font& font, float windowWidth, float windowHeight, int currentPrize, const std::map<std::string, int>& prizeMultipliers, sf::Sound& prizeSound);
void handleButtonInputs(const ButtonInputContext& context, sf::RenderWindow& window, bool& animateLogoFlag);





// Function to initialize UI elements
void initializeUIElements(const sf::Font& font, sf::RenderWindow& window, sf::Text& betLabelText, sf::Text& betValueText, sf::Text& creditsLabelText, sf::Text& creditsValueText, sf::Text& prizeValueOnlyText) {
    // Initialize the text elements with font, size, and position
    betLabelText.setFont(font);
    betLabelText.setCharacterSize(24);
    betLabelText.setString("Bet:");
    betLabelText.setPosition(20, window.getSize().y - 60);

    betValueText.setFont(font);
    betValueText.setCharacterSize(24);
    betValueText.setString("1");
    betValueText.setPosition(80, window.getSize().y - 60);

    creditsLabelText.setFont(font);
    creditsLabelText.setCharacterSize(24);
    creditsLabelText.setString("Credits:");
    creditsLabelText.setPosition(window.getSize().x - 200, window.getSize().y - 60);

    creditsValueText.setFont(font);
    creditsValueText.setCharacterSize(24);
    creditsValueText.setString("10");
    creditsValueText.setPosition(window.getSize().x - 100, window.getSize().y - 60);

    prizeValueOnlyText.setFont(font);
    prizeValueOnlyText.setCharacterSize(24);
    prizeValueOnlyText.setString("");
    prizeValueOnlyText.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2);
}




// Function to animate the logo
void animateLogo(sf::Sprite& logoSprite, float speed, float deltaTime, bool& animateLogoFlag, const sf::Vector2u& windowSize) {
    static float direction = 1.0f;

    if (animateLogoFlag) {
        sf::Vector2f position = logoSprite.getPosition();
        position.x += speed * direction * deltaTime;

        if (position.x + logoSprite.getGlobalBounds().width > windowSize.x || position.x < 0) {
            direction *= -1;
        }

        logoSprite.setPosition(position);
    }
}


void handleButtonInputs(const ButtonInputContext& context, sf::RenderWindow& window, bool& animateLogoFlag) {
    const sf::Event& event = context.event;
    static bool previousBKeyState = false;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::S) {
            if (!context.gameStarted) {
                context.soundManager.stopBackgroundMusic(); // Stop the music when the game starts
                startGame(context.window, context.font, context.prizeTexts, context.betAmount, context.prize, context.prizeMultipliers, context.soundManager.getPrizeSound(), context.canBet);
                context.gameStarted = true;
                std::cout << "[Debug] Starting game and stopping background music" << std::endl;
            } else {
                resetGameState(context.playerCredits, context.betAmount, context.canCollect, context.drawFiveCards, context.hand, context.deck, context.prizeTexts, context.font, context.window, context.backgroundSprite, context.instructions, context.creditsLabelText, context.creditsValueText, context.betLabelText, context.betValueText, context.prizeValueOnlyText, context.soundManager);
                updateUI(window, context.backgroundSprite, context.instructions, context.creditsLabelText, context.creditsValueText, context.betLabelText, context.betValueText, context.prizeTexts, context.hand, context.gameOverText, context.gameOver, context.playerCredits, context.betAmount);

                std::cout << "[Debug] Game reset" << std::endl; // Removed playing win sound
            }

            animateLogoFlag = false; // Stop the logo animation
            std::cout << "[Debug] Game State Reset Completed and Prize Texts Updated!" << std::endl;
        }

        if (context.gameStarted && context.canBet && event.key.code == sf::Keyboard::B && context.playerCredits > 0) {
            handleBetPlacement(event, context.canBet, context.betAmount, context.playerCredits, context.prizeTexts, context.font, context.betText, window, context.soundManager);
            context.soundManager.getCardDealSound().play(); // Play card deal sound when bet is placed
            context.betValueText.setString(std::to_string(context.betAmount));
            previousBKeyState = true;
            std::cout << "[Debug] Bet Placed: " << context.betAmount << ", playing card deal sound" << std::endl;
        }
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B) {
        previousBKeyState = false;
        std::cout << "[Debug] B Key Released" << std::endl;
    }
}



int main() {
    // Ensure working directory is set to project root
    fs::current_path("D:/Programming/Projects/Softypoker");

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SoftyPoker");
    sf::View view(sf::FloatRect(0, 0, 1280, 720));
    window.setView(view);

    // Output the current working directory
    std::cout << "Current working directory: " << fs::current_path() << std::endl;

    // Load fonts, sounds, etc.
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arialnbi.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    SoundManager soundManager;
    try {
        soundManager.initializeAllSounds();
        soundManager.playRandomBackgroundMusic(); // Start playing background music
    } catch (const std::exception& e) {
        std::cerr << "Sound initialization error: " << e.what() << std::endl;
        return -1;
    }

    sf::Text creditsLabelText, creditsValueText, betLabelText, betValueText, instructions, gameOverText, prizeValueOnlyText;
    std::vector<sf::Text> prizeTexts;
    int betAmount = 1, playerCredits = 10, prize = 0;
    bool canBet = true, gameStarted = false, drawFiveCards = true, roundInProgress = false, gameOver = false, gamblingPhase = false;
    std::vector<Card> hand, deck = createDeck();
    sf::Sprite backgroundSprite, logoSprite;
    sf::Texture logoTexture; // Declare logoTexture here

    std::vector<sf::Texture> backgroundTextures;
    std::vector<std::string> backgroundPaths = {
        "assets/images/fantasy_girl.png",
        "assets/images/fire_girl.png",
        "assets/images/sofa_girl.png",
        "assets/images/claws_girl.png",
        "assets/images/blond_girl.png",
        "assets/images/skul_girl.png"
    };

    for (const auto& path : backgroundPaths) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load texture from " << path << std::endl;
            return -1;
        }
        backgroundTextures.push_back(texture);
    }

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int randomIndex = std::rand() % backgroundTextures.size();

    backgroundSprite.setTexture(backgroundTextures[randomIndex]);

    // Ensure the background is scaled and positioned correctly
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundSprite.getGlobalBounds().width,
        static_cast<float>(window.getSize().y) / backgroundSprite.getGlobalBounds().height
    );
    backgroundSprite.setPosition(0, 0);

    if (!logoTexture.loadFromFile("assets/images/logo.png")) {
        std::cerr << "Failed to load logo texture" << std::endl;
        return -1;
    }

    logoSprite.setTexture(logoTexture);
    logoSprite.setScale(0.25f, 0.25f); // Scale the logo as needed

    initializeUIElements(font, window, betLabelText, betValueText, creditsLabelText, creditsValueText, prizeValueOnlyText);

    // Ensure instructions are initialized
    instructions.setFont(font);
    instructions.setCharacterSize(32);
    instructions.setFillColor(sf::Color::Red);
    instructions.setString("Press 'S' to start, 'B' to bet. In Building Phase ©2025 By T.E. & E.M.");
    instructions.setPosition((window.getSize().x - instructions.getLocalBounds().width) / 2.f, 10.f);

    // Ensure prize texts are initialized
    // Example call to updatePrizeTexts
    updatePrizeTexts(prizeTexts, betAmount, font, window.getSize().x, window.getSize().y, prize, prizeMultipliers, soundManager.getPrizeSound());
    // Trigger initial resizing to ensure UI elements are positioned correctly at the start
    handleResize(window, view, backgroundSprite, logoSprite, window.getSize().x, window.getSize().y, soundManager, betLabelText, betValueText, creditsLabelText, creditsValueText, prizeTexts, prizeValueOnlyText, instructions);

    sf::Clock clock;
    float speed = 200.0f; // Adjust speed as needed

    bool animateLogoFlag = true; // Initialize the logo animation flag

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                handleResize(window, view, backgroundSprite, logoSprite, event.size.width, event.size.height, soundManager, betLabelText, betValueText, creditsLabelText, creditsValueText, prizeTexts, prizeValueOnlyText, instructions);
            } else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                ButtonInputContext context{
                    event, hand, canBet, betAmount, canCollect, prize, playerCredits, drawFiveCards,
                    roundInProgress, gameOver, deck, window, backgroundSprite, creditsText, betText,
                    gameStarted, prizeTexts, font, soundManager.getCardDealSound(), soundManager.getHeldSound(),
                    soundManager.getUnheldSound(), soundManager.getCountSound(), instructions,
                    gameOverText, gamblingPhase, soundManager, creditsLabelText, creditsValueText, betLabelText,
                    betValueText, prizeMultipliers
                };
                handleButtonInputs(context, window, animateLogoFlag);
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Animate the logo
        animateLogo(logoSprite, speed, deltaTime, animateLogoFlag, window.getSize());

        // Clear window and draw all elements once per frame to avoid flickering
        window.clear();
        window.draw(backgroundSprite);
        window.draw(logoSprite); // Draw the logo sprite

        // Draw UI elements
        window.draw(creditsLabelText);
        window.draw(creditsValueText);
        window.draw(betLabelText);
        window.draw(betValueText);
        window.draw(instructions); // Ensure instructions are drawn in the correct position
        window.draw(prizeValueOnlyText); // Ensure this is drawn only once
        for (const auto& prizeText : prizeTexts) {
            window.draw(prizeText);
        }
        window.draw(gameOverText);
        window.display();
    }

    return 0;
}





















void startGame(sf::RenderWindow& window, const sf::Font& font, std::vector<sf::Text>& prizeTexts, int betAmount, int prize, const std::map<std::string, int>& prizeMultipliers, sf::Sound& prizeSound, bool& canBet);
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    updatePrizeTexts(prizeTexts, betAmount, font, windowWidth, windowHeight, prize, prizeMultipliers, prizeSound);
    canBet = false;
}




void resetGameState(int& playerCredits, int& betAmount, bool& canCollect, bool& drawFiveCards, std::vector<Card>& hand, std::vector<Card>& deck, std::vector<sf::Text>& prizeTexts, const sf::Font& font, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& instructions, sf::Text& creditsLabelText, sf::Text& creditsValueText, sf::Text& betLabelText, sf::Text& betValueText, sf::Text& prizeValueOnlyText, SoundManager& soundManager);
    playerCredits = 10;
    betAmount = 1;
    canCollect = false;
    drawFiveCards = true;
    hand.clear();
    deck = createDeck();
    shuffleDeck(deck);
    prize = 0;
    gameStarted = true;
    roundInProgress = false;
    gameOver = false;
    gamblingPhase = false;
    canBet = true;

    updatePrizeTexts(prizeTexts, betAmount, font, window.getSize().x, window.getSize().y, prize, prizeMultipliers, soundManager.getPrizeSound());

    creditsLabelText.setString("Credits: " + std::to_string(playerCredits));
    betLabelText.setString("Bet: " + std::to_string(betAmount));
}







void dealInitialHand(std::vector<Card>& deck, std::vector<Card>& hand, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& creditsLabelText, sf::Text& betText, const std::vector<sf::Text>& prizeTexts, SoundManager& soundManager) {
    hand.clear();
    float windowHeight = window.getSize().y;

    // Deactivate the B key
    canBet = false;

    for (int i = 0; i < 5; ++i) {
        hand.push_back(deck.back());
        deck.pop_back();
        hand.back().isHeld = false;  // Reset the isHeld state

        float scaleFactor = (windowHeight / 600.0f) * CARD_SCALE_FACTOR;
        hand.back().sprite.setScale(scaleFactor, scaleFactor);

        float xPos = CARD_LEFT_OFFSET + i * (hand.back().sprite.getGlobalBounds().width + CARD_SPACING);
        float yPos = windowHeight - CARD_BOTTOM_OFFSET - hand.back().sprite.getGlobalBounds().height;
        hand.back().sprite.setPosition(xPos, yPos);

        soundManager.getCardDealSound().play();

        window.clear();
        window.draw(backgroundSprite);
        window.draw(creditsLabelText);
        window.draw(betText);
        for (const auto& prizeText : prizeTexts) {
            window.draw(prizeText);
        }
        for (int j = 0; j <= i; ++j) {
            window.draw(hand[j].sprite);
        }
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}





void handleResize(sf::RenderWindow& window, sf::View& view, sf::Sprite& backgroundSprite, sf::Sprite& logoSprite, int newWidth, int newHeight, SoundManager& soundManager, sf::Text& betLabelText, sf::Text& betValueText, sf::Text& creditsLabelText, sf::Text& creditsValueText, std::vector<sf::Text>& prizeTexts, sf::Text& prizeValueOnlyText, sf::Text& instructions) {
    view.setSize(newWidth, newHeight);
    view.setCenter(newWidth / 2, newHeight / 2);
    window.setView(view);

    backgroundSprite.setScale(
        static_cast<float>(newWidth) / backgroundSprite.getTexture()->getSize().x,
        static_cast<float>(newHeight) / backgroundSprite.getTexture()->getSize().y
    );

    // Ensure the logo stays within bounds
    if (logoSprite.getPosition().x + logoSprite.getGlobalBounds().width > newWidth) {
        logoSprite.setPosition(newWidth - logoSprite.getGlobalBounds().width, logoSprite.getPosition().y);
    }
    if (logoSprite.getPosition().y + logoSprite.getGlobalBounds().height > newHeight) {
        logoSprite.setPosition(logoSprite.getPosition().x, newHeight - logoSprite.getGlobalBounds().height);
    }

    // Update UI elements positions and sizes dynamically
    updateUI(window, backgroundSprite, instructions, creditsLabelText, creditsValueText, betLabelText, betValueText, prizeTexts, hand, gameOverText, gameOver, playerCredits, betAmount);

    // Update prize value text position dynamically
    prizeValueOnlyText.setPosition(newWidth * 0.70f, newHeight * 0.50f + 40);

    // Update instructions position dynamically
    instructions.setPosition((newWidth - instructions.getLocalBounds().width) / 2.f, 10.f);
}





void updatePrizeTexts(std::vector<sf::Text>& prizeTexts, int betAmount, const sf::Font& font, float windowWidth, float windowHeight, int currentPrize, const std::map<std::string, int>& prizeMultipliers, sf::Sound& prizeSound) {
    prizeTexts.clear();
    std::vector<std::string> prizeNames = {
        "Super Royal", "Royal Flush", "Straight Flush",
        "Four of a Kind", "Full House", "Flush",
        "Straight", "Three of a Kind", "Two Pair", "Jacks or Better"
    };

    float prizeTableStartX = windowWidth * 0.70f;
    float prizeTableStartY = windowHeight * 0.09f;
    float characterSize = 22 * (windowHeight / 600.0f);

    for (size_t i = 0; i < prizeNames.size(); ++i) {
        sf::Text prizeText;
        prizeText.setFont(font);
        prizeText.setCharacterSize(characterSize);
        prizeText.setString(prizeNames[i] + " : " + std::to_string(prizeMultipliers.at(prizeNames[i]) * betAmount));
        prizeText.setPosition(prizeTableStartX, prizeTableStartY + i * (24 * (windowHeight / 600.0f)));

        if (currentPrize == prizeMultipliers.at(prizeNames[i]) * betAmount) {
            prizeText.setFillColor(sf::Color::Green);
            prizeSound.play();
        } else {
            prizeText.setFillColor(sf::Color(255, 102, 0));
        }

        prizeTexts.push_back(prizeText);
    }
}

void handleBetPlacement(const sf::Event& event, bool& canBet, int& betAmount, int& playerCredits, std::vector<sf::Text>& prizeTexts, const sf::Font& font, sf::Text& betText, sf::RenderWindow& window, SoundManager& soundManager) {
    if (event.key.code == sf::Keyboard::B && canBet && playerCredits > 0) {
        betAmount = (betAmount % 5) + 1;
        updatePrizeTexts(prizeTexts, betAmount, font, window.getSize().x, window.getSize().y, prize, prizeMultipliers, soundManager.getPrizeSound());
        betText.setString("Bet: " + std::to_string(betAmount));
    }
}







void updatePrizeValue(sf::Text& prizeValueOnlyText, int currentPrize) {
    prizeValueOnlyText.setString(std::to_string(currentPrize) + "-INIT"); // Update string while retaining identifier
}



















void updateUI(sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& instructions, sf::Text& creditsLabelText, sf::Text& creditsValueText, sf::Text& betLabelText, sf::Text& betValueText, std::vector<sf::Text>& prizeTexts, std::vector<Card>& hand, sf::Text& gameOverText, bool gameOver, int playerCredits, int betAmount) {
    float width = static_cast<float>(window.getSize().x);
    float height = static_cast<float>(window.getSize().y);
    float characterSize = 24 * (height / 600.0f); // Adjust character size dynamically

    creditsLabelText.setCharacterSize(characterSize);
    creditsLabelText.setPosition(10.f, height - 140.f);

    creditsValueText.setCharacterSize(characterSize);
    creditsValueText.setString(std::to_string(playerCredits));
    creditsValueText.setPosition(10.f + creditsLabelText.getLocalBounds().width + 5.f, height - 140.f);

    betLabelText.setCharacterSize(characterSize);
    betLabelText.setPosition(10.f, height - 90.f);

    betValueText.setCharacterSize(characterSize);
    betValueText.setString(std::to_string(betAmount));
    betValueText.setPosition(10.f + betLabelText.getLocalBounds().width + 5.f, height - 90.f);

    instructions.setPosition((width - instructions.getLocalBounds().width) / 2.f, 10.f);
    gameOverText.setPosition((width - gameOverText.getLocalBounds().width) / 2.f, height / 2.f);

    float prizeTableHeight = 60.f;
    for (size_t i = 0; i < prizeTexts.size(); ++i) {
        prizeTexts[i].setCharacterSize(22 * (height / 600.0f));
        prizeTexts[i].setPosition(width * 0.70f, prizeTableHeight + i * (24 * (height / 600.0f))); // Reduced gap further
    }

    float prizeValueX = width * 0.70f; // Adjusted to match prizetable
    float prizeValueY = height * 0.50f; // Adjusted to move further downwards

    for (auto& prizeText : prizeTexts) {
        if (prizeText.getString().toAnsiString().find("Prize:") != std::string::npos) {
            prizeText.setPosition(prizeValueX, prizeValueY);
        } else if (prizeText.getString().toAnsiString() == std::to_string(prize)) {
            prizeText.setFillColor(sf::Color(144, 238, 144)); // Light green color for prize value
            prizeText.setPosition(prizeValueX + prizeText.getLocalBounds().width + 20, prizeValueY + 40); // Move further to the right and downwards
        }
    }

    window.clear();
    window.draw(backgroundSprite);
    window.draw(instructions);
    window.draw(creditsLabelText);
    window.draw(creditsValueText);
    window.draw(betLabelText);
    window.draw(betValueText);
    for (const auto& prizeText : prizeTexts) {
        window.draw(prizeText);
    }
    for (const auto& card : hand) {
        window.draw(card.sprite);
    }
    if (gameOver) {
        window.draw(gameOverText);
    }
    window.display();
}











float calculateScaleFactor(const sf::RenderWindow& window) {
    return static_cast<float>(window.getSize().y) / 1080.0f; // Base on window height
}
























std::vector<Card> createDeck() {
    std::vector<Card> deck;
    const char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const char suits[] = {'H', 'D', 'C', 'S'};

    for (char suit : suits) {
        for (char rank : ranks) {
            Card card;
            card.suit = suit;
            card.rank = rank;
            std::string filePath = "D:/Programming/Projects/Assets/cards/" + std::string(1, rank) + std::string(1, suit) + ".png";
            if (loadTexture(card, filePath)) {
                deck.push_back(card);
            }
        }
    }
    return deck;
}



bool loadTexture(Card& card, const std::string& filePath) {
    card.texture = new sf::Texture();
    if (!card.texture->loadFromFile(filePath)) {
        delete card.texture;
        card.texture = nullptr;
        return false;
    }
    card.sprite.setTexture(*card.texture);
    return true;
}



void shuffleDeck(std::vector<Card>& deck) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}















void redrawHand(std::vector<Card>& deck, std::vector<Card>& hand, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& creditsLabelText, sf::Text& betText, const std::vector<sf::Text>& prizeTexts, sf::Sound& cardDealSound) {
    float windowHeight = window.getSize().y;

    for (int i = 0; i < 5; ++i) {
        if (!hand[i].isHeld) {
            hand[i] = deck.back();
            deck.pop_back();

            float scaleFactor = (windowHeight / 600.0f) * CARD_SCALE_FACTOR;
            hand[i].sprite.setScale(scaleFactor, scaleFactor);

            float xPos = CARD_LEFT_OFFSET + i * (hand[i].sprite.getGlobalBounds().width + CARD_SPACING);
            float yPos = windowHeight - CARD_BOTTOM_OFFSET - hand[i].sprite.getGlobalBounds().height;
            hand[i].sprite.setPosition(xPos, yPos);

            cardDealSound.play();

            window.clear();
            window.draw(backgroundSprite);
            window.draw(creditsLabelText);
            window.draw(betText);
            for (const auto& prizeText : prizeTexts) {
                window.draw(prizeText);
            }
            for (int j = 0; j < 5; ++j) {
                window.draw(hand[j].sprite);
            }
            window.display();

            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Smooth transition handling
        }
    }

    // Activate the B key after the redraw function
    canBet = true;
}






void drawHeldCardHighlight(sf::RenderWindow& window, const Card& card) {
    sf::RectangleShape highlight(sf::Vector2f(card.sprite.getGlobalBounds().width, card.sprite.getGlobalBounds().height));
    highlight.setPosition(card.sprite.getPosition());
    highlight.setFillColor(sf::Color::Transparent);
    highlight.setOutlineColor(sf::Color::Green);
    highlight.setOutlineThickness(5);
    window.draw(highlight);
}




int evaluateHand(const std::vector<Card>& hand, int betAmount) {
    if (hand.size() != 5) return 0;

    std::map<char, int> rankCount;
    std::map<char, int> suitCount;
    std::vector<int> rankValues;
    std::set<char> uniqueRanks;
    std::map<char, int> rankToValue = {
        {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
        {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}
    };

    for (const auto& card : hand) {
        rankCount[card.rank]++;
        suitCount[card.suit]++;
        rankValues.push_back(rankToValue[card.rank]);
        uniqueRanks.insert(card.rank);
    }

    std::sort(rankValues.begin(), rankValues.end());

    bool isFlush = (suitCount.size() == 1);
    bool isStraight = (uniqueRanks.size() == 5) &&
                      (((int)rankValues[4] - (int)rankValues[0] == 4) ||
                       (rankValues == std::vector<int>{2, 3, 4, 5, 14}));

    if (isFlush && uniqueRanks == std::set<char>{'T', 'J', 'Q', 'K', 'A'}) {
        return (hand[0].suit == 'H' ? 336 : 198) * betAmount;
    }

    if (isFlush && isStraight) {
        return 134 * betAmount; // Updated value
    }

    for (const auto& pair : rankCount) {
        if (pair.second == 4) return 72 * betAmount; // Updated value
    }

    bool threeOfAKind = false, pairFound = false;
    for (const auto& pair : rankCount) {
        if (pair.second == 3) threeOfAKind = true;
        if (pair.second == 2) pairFound = true;
    }
    if (threeOfAKind && pairFound) return 36 * betAmount;
    if (isFlush) return 19 * betAmount;
    if (isStraight) return 11 * betAmount; // Updated value
    for (const auto& pair : rankCount) {
        if (pair.second == 3) return 7 * betAmount; // Updated value
    }
    int pairCount = 0;
    for (const auto& pair : rankCount) {
        if (pair.second == 2) pairCount++;
    }
    if (pairCount == 2) return 3 * betAmount; // Updated value
    if (rankCount['J'] == 2 || rankCount['Q'] == 2 || rankCount['K'] == 2 || rankCount['A'] == 2) return 1 * betAmount;

    // Re-enable the B key
    canBet = true;

    return 0;
}









void initializeGamblingGame(std::vector<Card>& deck, Card& currentCard) {
    deck = createDeck();
    shuffleDeck(deck);
    currentCard = deck.back();
    deck.pop_back();

    // Set the initial position and scale for the card
    currentCard.sprite.setPosition(200, 100); // Example position, adjust as needed
    currentCard.sprite.setScale(0.13f, 0.13f); // Example scale, adjust as needed

    // Debug statement to confirm texture loading
    if (!currentCard.texture) {
        std::cerr << "Failed to load current card texture" << std::endl;
    }
    // Debug statement to check card position and scale
    // std::cout << "Card Position: " << currentCard.sprite.getPosition().x << ", " << currentCard.sprite.getPosition().y << std::endl;
    // std::cout << "Card Scale: " << currentCard.sprite.getScale().x << ", " << currentCard.sprite.getScale().y << std::endl;
}




void updateCardPositionsAndScales(std::vector<Card>& cards, sf::RenderWindow& window) {
    for (auto& card : cards) {
        float scaleFactor = (window.getSize().y / 600.0f) * CARD_SCALE_FACTOR;
        card.sprite.setScale(scaleFactor, scaleFactor);

        // Ensure the card is positioned within the window's bounds
        float xPos = std::min(CARD_LEFT_OFFSET + (&card - &cards[0]) * (card.sprite.getGlobalBounds().width + CARD_SPACING), window.getSize().x - card.sprite.getGlobalBounds().width);
        float yPos = std::min(window.getSize().y - CARD_BOTTOM_OFFSET - card.sprite.getGlobalBounds().height, window.getSize().y - card.sprite.getGlobalBounds().height);

        card.sprite.setPosition(xPos, yPos);

            // Debug statements to check card position and scale
            // std::cout << "Card Position: " << card.sprite.getPosition().x << ", " << card.sprite.getPosition().y << std::endl;
            // std::cout << "Card Scale: " << card.sprite.getScale().x << ", " << card.sprite.getScale().y << std::endl;
    }
}

std::vector<Card> createGamblingDeck() {
    std::vector<Card> deck;
    const char highRanks[] = {'8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const char lowRanks[] = {'2', '3', '4', '5', '6', '7'};

    const char suits[] = {'H', 'D', 'C', 'S'};

    for (char suit : suits) {
        for (char rank : highRanks) {
            Card card;
            card.suit = suit;
            card.rank = rank;
            std::string filePath = "D:/Programming/Projects/Assets/cards/" + std::string(1, rank) + std::string(1, suit) + ".png";
            if (loadTexture(card, filePath)) {
                deck.push_back(card);
            }
        }
        for (char rank : lowRanks) {
            Card card;
            card.suit = suit;
            card.rank = rank;
            std::string filePath = "D:/Programming/Projects/Assets/cards/" + std::string(1, rank) + std::string(1, suit) + ".png";
            if (loadTexture(card, filePath)) {
                deck.push_back(card);
            }
        }
    }
    return deck;
}




void startGamblingPhase(sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& creditsText, sf::Text& betText, std::vector<sf::Text>& prizeTexts, const sf::Font& font, int& prize, int& playerCredits, std::vector<Card>& deck, std::vector<Card>& hand, sf::Sound& loseSound, sf::Sound& winSound, sf::Sound& countSound) {
    static std::vector<Card> gamblingDeck;
    static Card currentGamblingCard;
    static bool isInitialized = false;
    static std::unordered_set<int> usedCards;

    if (!isInitialized) {
        initializeGamblingGame(gamblingDeck, currentGamblingCard);
        isInitialized = true;
    }

    bool gamblingActive = true;
    bool showCard = false;

    float windowHeight = window.getSize().y;
    float scaleFactor = (windowHeight / 600.0f) * CARD_SCALE_FACTOR;
    updateCardPositionsAndScales(gamblingDeck, window);
    currentGamblingCard.sprite.setScale(scaleFactor, scaleFactor);

    if (hand.size() >= 3) {
        currentGamblingCard.sprite.setPosition(hand[2].sprite.getPosition());
    }

    while (gamblingActive && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyPressed) {
                bool correctGuess = false;
                if (event.key.code == sf::Keyboard::Left) {
                    correctGuess = playGamblingRound(gamblingDeck, currentGamblingCard, false, usedCards);
                } else if (event.key.code == sf::Keyboard::Right) {
                    correctGuess = playGamblingRound(gamblingDeck, currentGamblingCard, true, usedCards);
                } else if (event.key.code == sf::Keyboard::C) {
                    int transferStep = 1;
                    sf::Clock clock;

                    while (prize > 0) {
                        prize -= transferStep;
                        playerCredits += transferStep;
                        countSound.play();

                        creditsText.setString("Credits: " + std::to_string(playerCredits));

                        window.clear();
                        window.draw(backgroundSprite);
                        window.draw(creditsText);
                        window.draw(betText);

                        if (showCard) {
                            window.draw(currentGamblingCard.sprite);
                        }
                        window.display();

                        while (clock.getElapsedTime().asMilliseconds() < 200) {
                        }
                        clock.restart();
                    }
                    gamblingActive = false;
                    canBet = true;
                    return;
                }

                showCard = true;
                if (!correctGuess) {
                    loseSound.play();
                    prize = 0;
                    gamblingActive = false;  // Ends the gambling on incorrect guess
                } else {
                    winSound.play();
                    prize *= 2;  // Continues gambling with doubled prize
                }
            }
        }

        // Update UI for gambling phase, excluding prize table
        window.clear();
        window.draw(backgroundSprite);
        window.draw(creditsText);
        window.draw(betText);
        if (showCard) {
            window.draw(currentGamblingCard.sprite);
        }
        window.display();
    }
}


bool playGamblingRound(std::vector<Card>& deck, Card& currentCard, bool guessHigher, std::unordered_set<int>& usedCards) {
    if (deck.empty()) {
        initializeGamblingGame(deck, currentCard); // Reshuffle the deck if empty
        usedCards.clear(); // Clear used cards when deck is reshuffled
    }

    Card nextCard;
    int attempts = 0;
    const int maxAttempts = deck.size(); // Maximum attempts based on deck

    do {
        if (deck.empty() || attempts >= maxAttempts) {
            initializeGamblingGame(deck, currentCard); // Reshuffle the deck
            usedCards.clear(); // Clear used cards for reuse
            attempts = 0;
        }
        nextCard = deck.back();
        deck.pop_back();
        attempts++;
    } while (usedCards.find(nextCard.getRankAsInt()) != usedCards.end());

    int currentRank = currentCard.getRankAsInt();
    int nextRank = nextCard.getRankAsInt();

    bool correctGuess = guessHigher ? (nextRank > currentRank) : (nextRank < currentRank);

    usedCards.insert(currentCard.getRankAsInt());
    currentCard = nextCard; // Update current card to next card

    return correctGuess;
}





