#include "TextScroll.h"

TextScroll::TextScroll(const sf::Font& font, const std::string& textStr, float speed, float startY)
    : speed(speed) {
    text.setFont(font);
    text.setString(textStr);
    text.setPosition(0, startY);
}

// TextScroll.cpp
void TextScroll::setTextColor(const sf::Color& color) {
    text.setFillColor(color);
}


void TextScroll::update(sf::Time elapsed) {
    text.move(-speed * elapsed.asSeconds(), 0);
    if (text.getPosition().x + text.getGlobalBounds().width < 0) {
        text.setPosition(1280, text.getPosition().y);
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

void TextScroll::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text, states);
}

