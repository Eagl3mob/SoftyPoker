#include "IntroState.h"
#include "Utility.h"
#include <iostream>
#include <vector>
#include <random>

namespace SoftyPoker {

IntroState::IntroState(SoundManager& sp, sf::RenderWindow& window)
    : soundPlayer(sp),
      firstLine(TextScroll(font, "Hello and welcome to SoftyPoker project intro. Starting in 2025 with the help from AI, using SFML2, Code::Blocks and many other open-source great goodies. SoftyPoker's expected finish date is when it is done. The objective is to make a kind of card game where the player plays against the odds, similar to a video poker clone. The player will have 5 cards dealt on the draw, then choose which cards to hold or not. The held cards will be replaced. Based on the redraw, the hand will be evaluated, and from there, there will be a prize table where, according to what the player has on hand, they will know if there is a prize or not. The player has the choice, if there is a prize, to double the prize or lose it by guessing if a card is lower or higher. And so on... more to be implemented as the code continues to develop. More T.B.A...", 300.0f, window.getSize().y / 1.2f)),
      secondLine(TextScroll(font, "Softy Projects © 2025 by T.E. & E.M. is licensed under a Creative Commons Attribution 4.0 International License (CC BY 4.0). This includes all sub-projects such as SoftyPoker.", 150.0f, window.getSize().y / 1.2f + 50)),
      logoAnimation(logoTexture, 12.0f),
      backgroundHandler(backgroundTexture) {

    backgroundFiles = {
        getAssetPath("images/backgrounds/blond_girl.png"),
        getAssetPath("images/backgrounds/claws_girl.png"),
        getAssetPath("images/backgrounds/fantasy_girl.png"),
        getAssetPath("images/backgrounds/fire_girl.png"),
        getAssetPath("images/backgrounds/skul_girl.png"),
        getAssetPath("images/backgrounds/sofa_girl.png")
    };

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, backgroundFiles.size() - 1);
    int index = dis(g);

    std::string selectedFile = backgroundFiles[index];
    std::cout << "[Debug] Loading background texture: " << selectedFile << std::endl;

    if (!backgroundTexture.loadFromFile(selectedFile)) {
        throw std::runtime_error("Failed to load background texture: " + selectedFile);
    } else {
        std::cout << "[Debug] Successfully loaded background texture: " << selectedFile << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!logoTexture.loadFromFile(getAssetPath("images/logo.png"))) {
        throw std::runtime_error("Failed to load logo texture");
    }
    logoSprite.setTexture(logoTexture);
    logoSprite.setScale(0.3f, 0.3f);

    if (!font.loadFromFile(getAssetPath("fonts/arialnbi.ttf"))) {
        throw std::runtime_error("Failed to load font");
    }

    soundPlayer.initializeMusic();
    soundPlayer.playRandomBackgroundMusic();

    resizeElements(window);
}

void IntroState::resizeElements(sf::RenderWindow& window) {
    ::resizeBackground(window, backgroundSprite, backgroundTexture);

    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    // Scale and position the logo sprite
    float logoScaleX = 0.3f * (windowWidth / 1280.f);
    float logoScaleY = 0.3f * (windowHeight / 720.f);
    logoSprite.setScale(logoScaleX, logoScaleY);
    logoSprite.setPosition(windowWidth / 12.f - logoSprite.getGlobalBounds().width / 2.f, windowHeight / 1.2f - logoSprite.getGlobalBounds().height / 2.f);

    // Adjust character size and position for the first line of text
    firstLine.setCharacterSize(static_cast<unsigned int>(32 * (windowWidth / 1280.f))); // Adjust character size based on window width
    firstLine.setPosition(windowWidth, windowHeight / 1.2f);

    // Adjust character size and position for the second line of text
    secondLine.setCharacterSize(static_cast<unsigned int>(40 * (windowWidth / 1280.f))); // Adjust character size based on window width
    secondLine.setPosition(firstLine.getPosition().x + horizontalOffset, firstLine.getPosition().y + firstLine.getLocalBounds().height + 5);
}

void IntroState::update(sf::RenderWindow& window) {
    sf::Time elapsed = clock.restart();
    logoAnimation.update(elapsed);
    firstLine.update(elapsed);
    secondLine.update(elapsed);
}

void IntroState::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(firstLine);
    window.draw(logoSprite);
    window.draw(secondLine);
    window.display();
}

void IntroState::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    if (event.type == sf::Event::Resized) {
        sf::View view = window.getView();
        view.setSize(event.size.width, event.size.height);
        window.setView(view);
        resizeElements(window);
    }
}

void IntroState::animateLogo() {
    float fadeElapsed = fadeClock.getElapsedTime().asSeconds();
    float fadeProgress = std::fmod(fadeElapsed, fadeDuration) / fadeDuration;

    if (fadeProgress < 0.5f) {
        sf::Uint8 alpha = static_cast<sf::Uint8>(255 * (fadeProgress * 2.0f));
        logoSprite.setColor(sf::Color(255, 255, 255, alpha));
    } else {
        sf::Uint8 alpha = static_cast<sf::Uint8>(255 * ((1.0f - fadeProgress) * 2.0f));
        logoSprite.setColor(sf::Color(255, 255, 255, alpha));
    }
}

// ... existing content ...

void IntroState::scrollText(sf::RenderWindow& window, sf::Time elapsed) {
    sf::Vector2f firstLinePos = firstLine.getPosition();
    firstLinePos.x -= firstLineSpeed * elapsed.asSeconds();
    if (firstLinePos.x + firstLine.getLocalBounds().width < 0) {
        firstLinePos.x = window.getSize().x;
    }
    firstLine.setPosition(firstLinePos);

    sf::Vector2f secondLinePos = secondLine.getPosition();
    secondLinePos.x -= secondLineSpeed * elapsed.asSeconds();
    if (secondLinePos.x + secondLine.getLocalBounds().width < 0) {
        secondLinePos.x = window.getSize().x + horizontalOffset;
    }
    secondLine.setPosition(secondLinePos);
}

} // namespace SoftyPoker  // Ensure this closing brace is present

