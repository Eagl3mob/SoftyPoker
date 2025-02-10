#include "IntroState.h"
#include "Utility.h"
#include <iostream>
#include <vector>
#include <random>

namespace SoftyPoker {

IntroState::IntroState(SoundManager& sp, sf::RenderWindow& window)
    : soundPlayer(sp),
      font(),
      firstLine(TextScroll(font, "Hello and welcome to SoftyPoker project intro. Starting in 2025 with the help from AI, using SFML2, Code::Blocks and many other open-source great goodies. SoftyPoker is a fun project to help learn and create together.", 100.0f, window.getSize().y / 1.2f, window.getSize().x)),
      secondLine(TextScroll(font, "Softy Projects © 2025 by T.E. & E.M. is licensed under a Creative Commons Attribution 4.0 International License (CC BY 4.0). This includes all sub-projects such as SoftyPoker.", 200.0f, window.getSize().y / 1.1f, window.getSize().x)),
      logoAnimation(logoTexture, 12.0f),
      backgroundHandler(backgroundTexture),
      fadeDuration(6.0f),
      pauseDuration(2.0f),
      totalElapsed(sf::Time::Zero),
      firstLineSpeed(140.0f),
      secondLineSpeed(200.0f) {

    firstLine.setTextColor(sf::Color(144, 238, 144));
    secondLine.setTextColor(sf::Color(144, 238, 144));

    // Initialize instructionText
    instructionText.setFont(font);
    instructionText.setString("S to Start Game...Not YET !!!");
    instructionText.setCharacterSize(50);
    instructionText.setFillColor(sf::Color(173, 216, 230)); // Set the color to light blue

    backgroundFiles = {
        getAssetPath("images/backgrounds/blond_girl.png"),
        getAssetPath("images/backgrounds/claws_girl.png"),
        getAssetPath("images/backgrounds/fantasy_girl.png"),
        getAssetPath("images/backgrounds/fire_girl.png"),
        getAssetPath("images/backgrounds/skul_girl.png"),
        getAssetPath("images/backgrounds/sofa_girl.png"),
        getAssetPath("images/backgrounds/bikini_girl.png")
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
    logoSprite.setScale(0.2f, 0.2f);

    if (!font.loadFromFile(getAssetPath("fonts/arialnbi.ttf"))) {
        throw std::runtime_error("Failed to load font");
    }

    soundPlayer.initializeMusic();
    soundPlayer.playRandomBackgroundMusic();

    secondLine.enableSmoothColorTransition(true);
    secondLine.setColorFadeSpeed(0.1f);

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
    secondLine.setPosition(windowWidth, windowHeight / 1.1f);

    firstLine.setWindowWidth(windowWidth);
    secondLine.setWindowWidth(windowWidth);

    // Set the position of instructionText to the top left
    instructionText.setPosition(10.0f, 10.0f);
}

void IntroState::update(sf::RenderWindow& window) {
    sf::Time elapsed = clock.restart();
    totalElapsed += elapsed;
    logoAnimation.update(elapsed);
    firstLine.update(elapsed, totalElapsed);
    secondLine.update(elapsed, totalElapsed);
    scrollText(window, elapsed);
    animateLogo();
}

void IntroState::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(firstLine);
    window.draw(logoSprite);
    window.draw(secondLine);
    window.draw(instructionText); // Draw the instructionText
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
        logoSprite.setColor(sf::Color(255, 255, 255, alpha));
    } else if (cycleProgress < (fadeDuration + pauseDuration) / totalDuration) {
        logoSprite.setColor(sf::Color(255, 255, 255, 255));
    } else {
        float fadeProgress = (cycleProgress - (fadeDuration + pauseDuration) / totalDuration) / (fadeDuration / totalDuration);
        sf::Uint8 alpha = static_cast<sf::Uint8>(255 * (1.0f - fadeProgress));
        logoSprite.setColor(sf::Color(255, 255, 255, alpha));
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
        secondLinePos.x = window.getSize().x;
    }
    secondLine.setPosition(secondLinePos);
}

} // namespace SoftyPoker
