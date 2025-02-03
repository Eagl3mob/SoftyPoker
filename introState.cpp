#include "introState.h"
#include "Utility.h"
#include <iostream>
#include <vector>
#include <random>

// Function to resize and center the background image
void resizeBackground(sf::RenderWindow& window, sf::Sprite& backgroundSprite, const sf::Texture& backgroundTexture) {
    sf::Vector2f windowSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    sf::Vector2f textureSize(static_cast<float>(backgroundTexture.getSize().x), static_cast<float>(backgroundTexture.getSize().y));

    // Calculate scaling factors to maintain aspect ratio
    float scaleX = windowSize.x / textureSize.x;
    float scaleY = windowSize.y / textureSize.y;
    float scale = std::max(scaleX, scaleY); // Scale to cover the entire window

    backgroundSprite.setScale(scale, scale);

    // Center the background
    backgroundSprite.setPosition(
        (windowSize.x - textureSize.x * scale) / 2,
        (windowSize.y - textureSize.y * scale) / 2
    );
}

void introState(sf::RenderWindow& window, SoundManager& soundManager) {
    sf::Clock clock;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text firstLine;
    sf::Text secondLine;

    // List of background files to choose from
    std::vector<std::string> backgroundFiles = {
        getAssetPath("images/blond_girl.png"),
        getAssetPath("images/claws_girl.png"),
        getAssetPath("images/fantasy_girl.png"),
        getAssetPath("images/fire_girl.png"),
        getAssetPath("images/skul_girl.png"),
        getAssetPath("images/sofa_girl.png")
    };

    // Randomly select a background image
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, backgroundFiles.size() - 1);
    int index = dis(g);

    if (!backgroundTexture.loadFromFile(backgroundFiles[index])) {
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Load logo texture and set sprite
    if (!logoTexture.loadFromFile(getAssetPath("images/logo.png"))) {
        return;
    }
    logoSprite.setTexture(logoTexture);

    // Scale down the logo sprite
    logoSprite.setScale(0.3f, 0.3f); // Adjust the scale factor to make the logo smaller

    // Position the logo more to the left and downward
    logoSprite.setPosition(window.getSize().x / 12.f - logoSprite.getGlobalBounds().width / 2.f, window.getSize().y / 1.2f - logoSprite.getGlobalBounds().height / 2.f);

    // Initial call to center background and logo
    resizeBackground(window, backgroundSprite, backgroundTexture);

    // Load font and set scrolling text
    if (!font.loadFromFile(getAssetPath("fonts/arialnbi.ttf"))) {
        return;
    }

    // Create the first line of text
    firstLine.setFont(font);
    firstLine.setString("Hello and welcome to SoftyPoker project intro. Starting in 2025 with the help from AI, using SFML2, Code::Blocks and many other open-source great goodies. SoftyPoker's expected finish date is when it is done. The objective is to make a kind of card game where the player plays against the odds, similar to a video poker clone. The player will have 5 cards dealt on the draw, then choose which cards to hold or not. The held cards will be replaced. Based on the redraw, the hand will be evaluated, and from there, there will be a prize table where, according to what the player has on hand, they will know if there is a prize or not. The player has the choice, if there is a prize, to double the prize or lose it by guessing if a card is lower or higher. And so on... more to be implemented as the code continues to develop. More T.B.A...");
    firstLine.setCharacterSize(32);
    firstLine.setFillColor(sf::Color::Green);
    firstLine.setPosition(window.getSize().x, window.getSize().y / 1.2f);

    // Create the second line of text

    secondLine.setFont(font);
    secondLine.setString("Softy Projects © 2025 by T.E. & E.M. is licensed under a Creative Commons Attribution 4.0 International License (CC BY 4.0). This includes all sub-projects such as SoftyPoker.");


    secondLine.setCharacterSize(40);
    secondLine.setFillColor(sf::Color::Red);
    secondLine.setPosition(window.getSize().x, firstLine.getPosition().y + firstLine.getLocalBounds().height + 5);

    // Define additional horizontal offset for the second line
    float horizontalOffset = 300.0f; // Further increased value for more shift to the right

    sf::Clock fadeClock; // Separate clock for fade-in effect

    soundManager.initializeMusic();
    soundManager.playRandomBackgroundMusic();

    float fadeDuration = 12.0f; // Duration of one fade cycle (slower fade)

    // Define different scroll speeds for the lines
    float firstLineSpeed = 300.0f; // Speed of the first line
    float secondLineSpeed = 150.0f; // Speed of the second line

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle window resize event
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));
                resizeBackground(window, backgroundSprite, backgroundTexture);

                // Adjust positions after resize
                firstLine.setPosition(window.getSize().x, window.getSize().y / 1.2f);
                secondLine.setPosition(firstLine.getPosition().x + horizontalOffset, firstLine.getPosition().y + firstLine.getLocalBounds().height + 5);
                logoSprite.setPosition(window.getSize().x / 12.f - logoSprite.getGlobalBounds().width / 2.f, window.getSize().y / 1.2f - logoSprite.getGlobalBounds().height / 2.f);
            }
        }

        // Animate logo (fading in and out)
        float fadeElapsed = fadeClock.getElapsedTime().asSeconds();
        float fadeProgress = std::fmod(fadeElapsed, fadeDuration) / fadeDuration;

        if (fadeProgress < 0.5f) {
            // Fading in
            sf::Uint8 alpha = static_cast<sf::Uint8>(255 * (fadeProgress * 2.0f));
            logoSprite.setColor(sf::Color(255, 255, 255, alpha));
        } else {
            // Fading out
            sf::Uint8 alpha = static_cast<sf::Uint8>(255 * ((1.0f - fadeProgress) * 2.0f));
            logoSprite.setColor(sf::Color(255, 255, 255, alpha));
        }

        // Scroll the first line
        sf::Vector2f firstLinePos = firstLine.getPosition();
        firstLinePos.x -= firstLineSpeed * elapsed.asSeconds(); // Scroll speed
        if (firstLinePos.x + firstLine.getLocalBounds().width < 0) {
            firstLinePos.x = window.getSize().x;
        }
        firstLine.setPosition(firstLinePos);

        // Scroll the second line
        sf::Vector2f secondLinePos = secondLine.getPosition();
        secondLinePos.x -= secondLineSpeed * elapsed.asSeconds(); // Scroll speed
        if (secondLinePos.x + secondLine.getLocalBounds().width < 0) {
            secondLinePos.x = window.getSize().x + horizontalOffset; // Restart scrolling with additional horizontal offset
        }
        secondLine.setPosition(secondLinePos);

        window.clear();
        window.draw(backgroundSprite); // Draw the background first
        window.draw(firstLine); // Then draw the first line of text under the logo
        window.draw(logoSprite); // Draw the logo as second
        window.draw(secondLine); // Draw the second line of text above the logo
        window.display();
    }
}
