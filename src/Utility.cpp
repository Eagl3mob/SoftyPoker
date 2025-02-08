#include "Utility.h"

void resizeBackground(sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Texture& backgroundTexture) {
    float windowRatio = static_cast<float>(window.getSize().x) / window.getSize().y;
    float textureRatio = static_cast<float>(backgroundTexture.getSize().x) / backgroundTexture.getSize().y;

    float scale;
    if (windowRatio > textureRatio) {
        scale = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    } else {
        scale = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    }

    backgroundSprite.setScale(scale, scale);

    sf::Vector2f newSize(
        backgroundTexture.getSize().x * scale,
        backgroundTexture.getSize().y * scale
    );
    backgroundSprite.setPosition(
        (window.getSize().x - newSize.x) / 2,
        (window.getSize().y - newSize.y) / 2
    );
}

std::string getAssetPath(const std::string& relativePath) {
    std::string basePath = "D:/Projects/softypoker/assets/";  // Update this to your actual assets path
    return basePath + relativePath;
}
