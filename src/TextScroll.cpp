#include <SFML/Graphics.hpp>
#include <cmath> // Include the cmath library for the sin function
#include "TextScroll.h"

TextScroll::TextScroll(const sf::Font& font, const std::string& textStr, float speed, float startY, float windowWidth)
    : speed(speed), windowWidth(windowWidth), enableColorTransition(false), colorFadeSpeed(1.0f) {
    text.setFont(font);
    text.setString(textStr);
    text.setPosition(windowWidth, startY);
}

void TextScroll::setTextColor(const sf::Color& color) {
    text.setFillColor(color);
}

void TextScroll::enableSmoothColorTransition(bool enable) {
    enableColorTransition = enable;
}

void TextScroll::setColorFadeSpeed(float speed) {
    colorFadeSpeed = speed;
}

void TextScroll::update(sf::Time elapsed, sf::Time totalElapsed) {
    text.move(-speed * elapsed.asSeconds(), 0);
    if (text.getPosition().x + text.getGlobalBounds().width < 0) {
        text.setPosition(windowWidth, text.getPosition().y);
    }

    if (enableColorTransition) {
        float time = totalElapsed.asSeconds() * colorFadeSpeed;
        sf::Uint8 red = static_cast<sf::Uint8>((std::sin(time) * 0.5f + 0.5f) * 255);
        sf::Uint8 green = static_cast<sf::Uint8>((std::sin(time + 2.0f) * 0.5f + 0.5f) * 255);
        sf::Uint8 blue = static_cast<sf::Uint8>((std::sin(time + 4.0f) * 0.5f + 0.5f) * 255);

        sf::Color fadeColor(red, green, blue);
        text.setFillColor(fadeColor);
    }
}

void TextScroll::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
}

void TextScroll::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void TextScroll::setPosition(sf::Vector2f position) {
    text.setPosition(position);
}

sf::Vector2f TextScroll::getPosition() const {
    return text.getPosition();
}

sf::FloatRect TextScroll::getLocalBounds() const {
    return text.getLocalBounds();
}

void TextScroll::setWindowWidth(float width) {
    windowWidth = width;
}

void TextScroll::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text, states);
}
