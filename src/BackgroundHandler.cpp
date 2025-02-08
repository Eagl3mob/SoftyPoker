#include "BackgroundHandler.h"

BackgroundHandler::BackgroundHandler(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

void BackgroundHandler::resize(sf::RenderWindow& window) {
    float windowRatio = static_cast<float>(window.getSize().x) / window.getSize().y;
    float textureRatio = static_cast<float>(sprite.getTexture()->getSize().x) / sprite.getTexture()->getSize().y;
    float scale;
    if (windowRatio > textureRatio) {
        scale = static_cast<float>(window.getSize().x) / sprite.getTexture()->getSize().x;
    } else {
        scale = static_cast<float>(window.getSize().y) / sprite.getTexture()->getSize().y;
    }
    sprite.setScale(scale, scale);
    sf::Vector2f newSize(sprite.getTexture()->getSize().x * scale, sprite.getTexture()->getSize().y * scale);
    sprite.setPosition((window.getSize().x - newSize.x) / 2, (window.getSize().y - newSize.y) / 2);
}

void BackgroundHandler::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

