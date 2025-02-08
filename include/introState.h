#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SoundManager.h"
#include "GameState.h"
#include "Utility.h"

namespace SoftyPoker {

class IntroState : public GameState {
public:
    IntroState(SoundManager& sp, sf::RenderWindow& window);
    void update(sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void resizeElements(sf::RenderWindow& window);

private:
    void initialize(sf::RenderWindow& window);
    void animateLogo();
    void scrollText(sf::RenderWindow& window, sf::Time elapsed);

    SoundManager& soundPlayer;
    sf::Clock clock;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text firstLine;
    sf::Text secondLine;
    std::vector<std::string> backgroundFiles;
    float fadeDuration;
    float firstLineSpeed;
    float secondLineSpeed;
    sf::Clock fadeClock;
    float horizontalOffset;
};

} // namespace SoftyPoker

#endif // INTRO_STATE_H
