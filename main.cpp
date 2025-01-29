

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Deck.h"
#include "Card.h"

// Constants
const float CARD_SCALE_FACTOR = 0.13f;
const float CARD_SPACING = 8.0f;
const float CARD_BOTTOM_OFFSET = 100.0f;
const float CARD_LEFT_OFFSET = 200.0f;
const std::string ASSET_DIR = "Assets/";

// Global Variables
sf::Font font;
std::unique_ptr<sf::Text> instructions;
std::unique_ptr<sf::Text> creditsText;
std::unique_ptr<sf::Text> betText;
std::unique_ptr<sf::Text> gameOverText;
std::vector<sf::Text> prizeTexts;
int betAmount = 1;
bool canBet = true;
bool gameOver = false;
bool gameStarted = false; // Add this global variable

// Function Prototypes
void initializeUIElements();
void initializeSounds(sf::Sound& cardDealSound, sf::Sound& heldSound, sf::Sound& unheldSound);
std::vector<Card> createDeck();
void shuffleDeck(std::vector<Card>& deck);
bool loadTexture(Card& card, const std::string& filePath);
void initializeGame(sf::RenderWindow& window, sf::Sprite& backgroundSprite, std::vector<Card>& deck, bool& canBet);
void handleButtonInputs(const sf::Event& event, std::vector<Card>& hand, bool& canBet, int& betAmount, bool& canCollect, int& prize, int& playerCredits, bool& drawFiveCards, bool& roundInProgress, bool& gameOver, std::vector<Card>& deck, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Sound& cardDealSound, sf::Sound& heldSound, sf::Sound& unheldSound, bool& gamblingPhase);
void updatePrizeTexts(std::vector<sf::Text>& prizeTexts, int betAmount, int windowWidth, int windowHeight, int prize);
void updateCardPositionsAndScales(std::vector<Card>& hand, sf::RenderWindow& window);
int evaluateHand(const std::vector<Card>& hand, int betAmount);

void initializeUIElements() {
    instructions = std::make_unique<sf::Text>("*S Start**B Bet**D Deal**1-5 Hold**G Gamble Low< >High**C Collect*", font, 24);
    instructions->setFillColor(sf::Color::Blue);
    instructions->setStyle(sf::Text::Italic);
    instructions->setPosition(sf::Vector2f(0, 2));

    creditsText = std::make_unique<sf::Text>("Credits: 0", font, 24);
    creditsText->setFillColor(sf::Color::White);
    creditsText->setStyle(sf::Text::Italic);
    creditsText->setPosition(sf::Vector2f(50, 250));

    betText = std::make_unique<sf::Text>("Bet: 0", font, 24);
    betText->setFillColor(sf::Color::White);
    betText->setStyle(sf::Text::Italic);
    betText->setPosition(sf::Vector2f(50, 280));

    gameOverText = std::make_unique<sf::Text>("GAME OVER", font, 30);
    gameOverText->setFillColor(sf::Color::Red);
    gameOverText->setStyle(sf::Text::Bold);
    gameOverText->setPosition(sf::Vector2f(50, 200));
}

void initializeSounds(sf::Sound& cardDealSound, sf::Sound& heldSound, sf::Sound& unheldSound) {
    static sf::SoundBuffer cardDealBuffer;
    if (!cardDealBuffer.loadFromFile(ASSET_DIR + "sounds/deal.wav")) {
        std::cerr << "Failed to open sound file '" + ASSET_DIR + "sounds/deal.wav'\n";
        throw std::runtime_error("Failed to load deal.wav");
    }
    cardDealSound.setBuffer(cardDealBuffer);
    cardDealSound.setVolume(100);

    static sf::SoundBuffer heldBuffer;
    if (!heldBuffer.loadFromFile(ASSET_DIR + "sounds/hold.wav")) {
        std::cerr << "Failed to open sound file '" + ASSET_DIR + "sounds/hold.wav'\n";
        throw std::runtime_error("Failed to load hold.wav");
    }
    heldSound.setBuffer(heldBuffer);
    heldSound.setVolume(100);

    static sf::SoundBuffer unheldBuffer;
    if (!unheldBuffer.loadFromFile(ASSET_DIR + "sounds/unheld.wav")) {
        std::cerr << "Failed to open sound file '" + ASSET_DIR + "sounds/unheld.wav'\n";
        throw std::runtime_error("Failed to load unheld.wav");
    }
    unheldSound.setBuffer(unheldBuffer);
    unheldSound.setVolume(100);
}

void initializeGame(sf::RenderWindow& window, sf::Sprite& backgroundSprite, std::vector<Card>& deck, bool& canBet) {
    static sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(ASSET_DIR + "backgrounds/space_cloud.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
        exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    initializeUIElements();
    deck = createDeck();
    shuffleDeck(deck);
    canBet = true;
}

void handleButtonInputs(const sf::Event& event, std::vector<Card>& hand, bool& canBet, int& betAmount, bool& canCollect, int& prize, int& playerCredits, bool& drawFiveCards, bool& roundInProgress, bool& gameOver, std::vector<Card>& deck, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Sound& cardDealSound, sf::Sound& heldSound, sf::Sound& unheldSound, bool& gamblingPhase) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::S && !gameStarted) {
            gameStarted = true;
            roundInProgress = true;
            canCollect = false;
            gameOver = false;
            playerCredits = 10;
            prize = 0;
            updatePrizeTexts(prizeTexts, betAmount, window.getSize().x, window.getSize().y, 0);
        } else if (event.key.code == sf::Keyboard::B && canBet) {
            if (betAmount < std::min(playerCredits, 5)) {
                betAmount++;
            } else {
                betAmount = 1;
            }
            updatePrizeTexts(prizeTexts, betAmount, window.getSize().x, window.getSize().y, prize);
            betText->setString("Bet: " + std::to_string(betAmount));
        } else if (event.key.code == sf::Keyboard::D && roundInProgress) {
            if (canBet && playerCredits >= betAmount) {
                playerCredits -= betAmount;
                creditsText->setString("Credits: " + std::to_string(playerCredits));
                hand.clear();
                for (int i = 0; i < 5; ++i) {
                    hand.push_back(std::move(deck.back()));
                    deck.pop_back();
                }
                updateCardPositionsAndScales(hand, window);
                drawFiveCards = false;
                canCollect = true;
                canBet = false;
                roundInProgress = false;
            }
        } else if (event.key.code == sf::Keyboard::C && canCollect) {
            prize = evaluateHand(hand, betAmount);
            playerCredits += prize;
            creditsText->setString("Credits: " + std::to_string(playerCredits));
            canCollect = false;
            canBet = true;
            gameOver = (playerCredits <= 0);
            if (!gameOver) {
                updatePrizeTexts(prizeTexts, betAmount, window.getSize().x, window.getSize().y, prize);
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SoftyPoker");

    if (!font.loadFromFile(ASSET_DIR + "fonts/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    initializeUIElements();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(*instructions);
        window.draw(*creditsText);
        window.draw(*betText);
        window.draw(*gameOverText);
        window.display();
    }

    return 0;
}








void dealInitialHand(std::vector<Card>& deck, std::vector<Card>& hand, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& creditsText, sf::Text& betText, const std::vector<sf::Text>& prizeTexts, sf::Sound& cardDealSound) {
    hand.clear();
    float windowHeight = window.getSize().y;

    for (int i = 0; i < 5; ++i) {
        hand.push_back(deck.back());
        deck.pop_back();

        float scaleFactor = (windowHeight / 600.0f) * CARD_SCALE_FACTOR;
        hand.back().sprite.setScale(scaleFactor, scaleFactor);

        float xPos = CARD_LEFT_OFFSET + i * (hand.back().sprite.getGlobalBounds().width + CARD_SPACING);
        float yPos = windowHeight - CARD_BOTTOM_OFFSET - hand.back().sprite.getGlobalBounds().height;
        hand.back().sprite.setPosition(xPos, yPos);

        cardDealSound.play();

        window.clear();
        window.draw(backgroundSprite);
        window.draw(creditsText);
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







void redrawHand(std::vector<Card>& deck, std::vector<Card>& hand, sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& creditsText, sf::Text& betText, const std::vector<sf::Text>& prizeTexts, sf::Sound& cardDealSound) {
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
            window.draw(creditsText);
            window.draw(betText);
            for (const auto& prizeText : prizeTexts) {
                window.draw(prizeText);
            }
            for (int j = 0; j < 5; ++j) {
                window.draw(hand[j].sprite);
            }
            window.display();

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    for (auto& card : hand) {
        card.isHeld = false;
    }
}



void drawHeldCardHighlight(sf::RenderWindow& window, const Card& card) {
    sf::RectangleShape highlight(sf::Vector2f(card.sprite.getGlobalBounds().width, card.sprite.getGlobalBounds().height));
    highlight.setPosition(card.sprite.getPosition());
    highlight.setFillColor(sf::Color::Transparent);
    highlight.setOutlineColor(sf::Color::Yellow);
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
        return 124 * betAmount;
    }

    for (const auto& pair : rankCount) {
        if (pair.second == 4) return 68 * betAmount;
    }

    bool threeOfAKind = false, pairFound = false;
    for (const auto& pair : rankCount) {
        if (pair.second == 3) threeOfAKind = true;
        if (pair.second == 2) pairFound = true;
    }
    if (threeOfAKind && pairFound) return 36 * betAmount;
    if (isFlush) return 19 * betAmount;
    if (isStraight) return 9 * betAmount;
    for (const auto& pair : rankCount) {
        if (pair.second == 3) return 4 * betAmount;
    }
    int pairCount = 0;
    for (const auto& pair : rankCount) {
        if (pair.second == 2) pairCount++;
    }
    if (pairCount == 2) return 2 * betAmount;
    if (rankCount['J'] == 2 || rankCount['Q'] == 2 || rankCount['K'] == 2 || rankCount['A'] == 2) return 1 * betAmount;

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
    std::cout << "Card Position: " << currentCard.sprite.getPosition().x << ", " << currentCard.sprite.getPosition().y << std::endl;
    std::cout << "Card Scale: " << currentCard.sprite.getScale().x << ", " << currentCard.sprite.getScale().y << std::endl;
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
        std::cout << "Card Position: " << card.sprite.getPosition().x << ", " << card.sprite.getPosition().y << std::endl;
        std::cout << "Card Scale: " << card.sprite.getScale().x << ", " << card.sprite.getScale().y << std::endl;
    }
}




void startGamblingPhase(sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Text& creditsText, sf::Text& betText, std::vector<sf::Text>& prizeTexts, const sf::Font& font, int& prize, int& playerCredits, bool& drawFiveCards, std::vector<Card>& mainGameDeck, std::vector<Card>& mainGameHand) {
    static std::vector<Card> gamblingDeck;
    static Card currentGamblingCard;
    static bool isInitialized = false;
    static std::unordered_set<int> usedCards;

    if (!isInitialized) {
        initializeGamblingGame(gamblingDeck, currentGamblingCard);
        isInitialized = true;
    }

    bool gamblingActive = true;
    bool showCardAfterLoss = false;

    // Ensure the current gambling card is resized correctly using CARD_SCALE_FACTOR
    float windowHeight = window.getSize().y;
    float scaleFactor = (windowHeight / 600.0f) * CARD_SCALE_FACTOR;
    updateCardPositionsAndScales(gamblingDeck, window);
    currentGamblingCard.sprite.setScale(scaleFactor, scaleFactor);

    // Set the current gambling card position to match the 2nd card from the main game
    if (mainGameHand.size() >= 2) {
        currentGamblingCard.sprite.setPosition(mainGameHand[1].sprite.getPosition());
    } else {
        std::cerr << "Main game hand does not contain enough cards." << std::endl;
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
                    playerCredits += prize;
                    prize = 0;
                    updatePrizeTexts(prizeTexts, 1, font, window.getSize().x, window.getSize().y, prize);
                    gamblingActive = false;
                    std::cout << "You collected your prize. Credits: " << playerCredits << std::endl;
                    continue;
                }

                if (!correctGuess) {
                    prize = 0;
                    updatePrizeTexts(prizeTexts, 1, font, window.getSize().x, window.getSize().y, prize);
                    gamblingActive = false;
                    showCardAfterLoss = true;
                    std::cout << "Incorrect guess! You lost your prize." << std::endl;

                    // Debug statements to check card position, scale, and texture
                    std::cout << "Card Position: " << currentGamblingCard.sprite.getPosition().x << ", " << currentGamblingCard.sprite.getPosition().y << std::endl;
                    std::cout << "Card Scale: " << currentGamblingCard.sprite.getScale().x << ", " << currentGamblingCard.sprite.getScale().y << std::endl;
                    if (!currentGamblingCard.texture) {
                        std::cerr << "Card texture is missing!" << std::endl;
                    }

                    // Ensure the card position matches the 2nd card from the main game
                    if (mainGameHand.size() >= 2) {
                        currentGamblingCard.sprite.setPosition(mainGameHand[1].sprite.getPosition());
                    }
                } else {
                    prize *= 2; // Double the prize on correct guess
                    updateCardPositionsAndScales(gamblingDeck, window);
                    currentGamblingCard.sprite.setScale(scaleFactor, scaleFactor); // Ensure the new card is resized correctly
                    currentGamblingCard.sprite.setPosition(mainGameHand[1].sprite.getPosition()); // Match position to 2nd card
                    updatePrizeTexts(prizeTexts, 1, font, window.getSize().x, window.getSize().y, prize);
                    std::cout << "Correct guess! Prize is now: " << prize << " Next card: " << currentGamblingCard.rank << currentGamblingCard.suit << std::endl;
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(creditsText);
        window.draw(betText);
        for (const auto& prizeText : prizeTexts) {
            window.draw(prizeText);
        }
        window.draw(currentGamblingCard.sprite); // Ensure the current gambling card is drawn
        window.display();

        if (!gamblingActive && showCardAfterLoss) {
            updateCardPositionsAndScales(gamblingDeck, window);
            currentGamblingCard.sprite.setScale(scaleFactor, scaleFactor); // Ensure the card is resized correctly
            currentGamblingCard.sprite.setPosition(mainGameHand[1].sprite.getPosition()); // Match position to 2nd card
            while (window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::D) {
                            showCardAfterLoss = false;
                            drawFiveCards = true;
                            isInitialized = false;
                            mainGameHand.clear();
                            initializeGamblingGame(mainGameDeck, currentGamblingCard);
                            return;
                        }
                    }
                }
                window.clear();
                window.draw(backgroundSprite);
                window.draw(creditsText);
                window.draw(betText);
                for (const auto& prizeText : prizeTexts) {
                    window.draw(prizeText);
                }
                window.draw(currentGamblingCard.sprite);
                window.display();
            }
        } else if (!gamblingActive) {
            drawFiveCards = true;
            isInitialized = false;
            return;
        }
    }
}



bool playGamblingRound(std::vector<Card>& deck, Card& currentCard, bool guessHigher, std::unordered_set<int>& usedCards) {
    if (deck.empty()) {
        initializeGamblingGame(deck, currentCard); // Reshuffle the deck if empty
    }

    Card nextCard;
    do {
        if (deck.empty()) {
            initializeGamblingGame(deck, currentCard); // Reshuffle if all cards are used
        }
        nextCard = deck.back();
        deck.pop_back();
    } while (usedCards.find(nextCard.getRankAsInt()) != usedCards.end() || nextCard.getRankAsInt() == currentCard.getRankAsInt());

    usedCards.insert(nextCard.getRankAsInt());

    int currentRank = currentCard.getRankAsInt();
    int nextRank = nextCard.getRankAsInt();

    bool correctGuess = false;
    if (guessHigher) {
        correctGuess = (nextRank > currentRank);
    } else {
        correctGuess = (nextRank < currentRank);
    }

    currentCard = nextCard; // Update the current card to the next card
    return correctGuess;
}









