#include "LogoAnimation.h"

LogoAnimation::LogoAnimation(const sf::Texture& texture, float fadeDuration)
    : fadeDuration(fadeDuration), fadingIn(true) {
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255, 255, 255, 0)); // Start fully transparent
}

void LogoAnimation::update(sf::Time elapsed) {
    sf::Time fadeTime = fadeClock.getElapsedTime();
    float alpha = (fadeTime.asSeconds() / fadeDuration) * 255;
    if (fadingIn) {
        if (alpha >= 255) {
            alpha = 255;
            fadingIn = false;
            fadeClock.restart();
        }
    } else {
        alpha = 255 - alpha;
        if (alpha <= 0) {
            alpha = 0;
            fadingIn = true;
            fadeClock.restart();
        }
    }
    sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
}

void LogoAnimation::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
