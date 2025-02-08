#ifndef LOGO_ANIMATION_H
#define LOGO_ANIMATION_H

#include <SFML/Graphics.hpp>

class LogoAnimation {
public:
    LogoAnimation(const sf::Texture& texture, float fadeDuration);
    void update(sf::Time elapsed);
    void draw(sf::RenderWindow& window);

    // Add method to set color
    void setColor(const sf::Color& color);

    // Add public methods to access and modify the sprite's position and scale
    void setPosition(float x, float y);
    void setScale(float scaleX, float scaleY);

private:
    sf::Sprite sprite;
    float fadeDuration;
    sf::Clock fadeClock;
    bool fadingIn;
};

#endif // LOGO_ANIMATION_H

