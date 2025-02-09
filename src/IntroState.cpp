#include "IntroState.h"
#include "Utility.h"
#include <iostream>
#include <vector>
#include <random>

namespace SoftyPoker {

IntroState::IntroState(SoundManager& sp, sf::RenderWindow& window)
    : soundPlayer(sp),
      firstLine(TextScroll(font, "Hello and welcome to SoftyPoker project intro. Starting in 2025 with the help from AI, using SFML2, Code::Blocks and many other open-source great goodies. SoftyPoker's experience is inspired by various card games and new technology.", 200.0f, 50.0f, window.getSize().x)), // Updated to include window width
      secondLine(TextScroll(font, "Softy Projects © 2025 by T.E. & E.M. is licensed under a Creative Commons Attribution 4.0 International License (CC BY 4.0). This includes all sub-projects such as SoftyPoker.", 400.0f, 100.0f, window.getSize().x)), // Updated to include window width
      logoAnimation(logoTexture, 12.0f),
      backgroundHandler(backgroundTexture),
      fadeDuration(6.0f),
      pauseDuration(2.0f) {  // Added pause duration

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
    } else {
        std::cout << "[Debug] Successfully loaded logo texture" << std::endl;
    }
    logoSprite.setTexture(logoTexture);
    // Make the logo a little smaller
    logoSprite.setScale(0.2f, 0.2f);

    if (!font.loadFromFile(getAssetPath("fonts/arialnbi.ttf"))) {
        throw std::runtime_error("Failed to load font");
    }

    soundPlayer.initializeMusic();
    soundPlayer.playRandomBackgroundMusic();

    // Set the text color for the first and second lines
    firstLine.setTextColor(sf::Color(144, 238, 144)); // Light green
    secondLine.setTextColor(sf::Color(255, 182, 193)); // Light red

    resizeElements(window);
}

void IntroState::resizeElements(sf::RenderWindow& window) {
    ::resizeBackground(window, backgroundSprite, backgroundTexture);

    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    float logoAspectRatio = logoTexture.getSize().x / static_cast<float>(logoTexture.getSize().y);
    float logoWidth = windowWidth * 0.2f;
    float logoHeight = logoWidth / logoAspectRatio;
    if (logoHeight > windowHeight * 0.2f) {
        logoHeight = windowHeight * 0.2f;
        logoWidth = logoHeight * logoAspectRatio;
    }
    logoSprite.setScale(logoWidth / logoTexture.getSize().x, logoHeight / logoTexture.getSize().y);
    logoSprite.setPosition(10.0f, windowHeight - logoHeight - 10.0f);

    firstLine.setCharacterSize(static_cast<unsigned int>(32 * (windowWidth / 1280.f)));
    firstLine.setPosition(windowWidth, windowHeight / 1.2f);

    secondLine.setCharacterSize(static_cast<unsigned int>(40 * (windowWidth / 1280.f)));
    secondLine.setPosition(firstLine.getPosition().x + horizontalOffset, firstLine.getPosition().y + firstLine.getLocalBounds().height + 5);

    // Update window width for text scrolling
    firstLine.setWindowWidth(windowWidth);
    secondLine.setWindowWidth(windowWidth);
}

void IntroState::update(sf::RenderWindow& window) {
    sf::Time elapsed = clock.restart();
    logoAnimation.update(elapsed);
    firstLine.update(elapsed);
    secondLine.update(elapsed);
    animateLogo();  // Ensure animateLogo is called
}

void IntroState::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(firstLine);
    window.draw(logoSprite); // Ensure the logo sprite is drawn here
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
    float totalDuration = fadeDuration * 2 + pauseDuration;
    float cycleProgress = std::fmod(fadeElapsed, totalDuration) / totalDuration;

    if (cycleProgress < fadeDuration / totalDuration) {
        float fadeProgress = cycleProgress / (fadeDuration / totalDuration);
        sf::Uint8 alpha = static_cast<sf::Uint8>(255 * fadeProgress);
        logoSprite.setColor(sf::Color(255, 255, 255, alpha)); // Fade in
    } else if (cycleProgress < (fadeDuration + pauseDuration) / totalDuration) {
        logoSprite.setColor(sf::Color(255, 255, 255, 255)); // Pause
    } else {
        float fadeProgress = (cycleProgress - (fadeDuration + pauseDuration) / totalDuration) / (fadeDuration / totalDuration);
        sf::Uint8 alpha = static_cast<sf::Uint8>(255 * (1.0f - fadeProgress));
        logoSprite.setColor(sf::Color(255, 255, 255, alpha)); // Fade out
    }
}

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

} // namespace SoftyPoker
