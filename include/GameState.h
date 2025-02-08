#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

class GameState {
public:
    GameState() = default;
    virtual void update(sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;  // Update signature
    virtual ~GameState() = default;
};

#endif // GAMESTATE_H
