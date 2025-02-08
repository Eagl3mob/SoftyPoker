#ifndef BACKGROUND_HANDLER_H
#define BACKGROUND_HANDLER_H

#include <SFML/Graphics.hpp>

class BackgroundHandler {
public:
    BackgroundHandler(const sf::Texture& texture);
    void resize(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
};

#endif // BACKGROUND_HANDLER_H

