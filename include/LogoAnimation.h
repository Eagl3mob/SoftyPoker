#ifndef LOGO_ANIMATION_H
#define LOGO_ANIMATION_H

#include <SFML/Graphics.hpp>

class LogoAnimation {
public:
    LogoAnimation(const sf::Texture& texture, float fadeDuration);
    void update(sf::Time elapsed);
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    float fadeDuration;
    sf::Clock fadeClock;
    bool fadingIn;
};

#endif // LOGO_ANIMATION_H
