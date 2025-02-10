#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "SoundManager.h"
#include "TextScroll.h"
#include "LogoAnimation.h"
#include "BackgroundHandler.h"

namespace SoftyPoker {

class IntroState : public GameState {
public:
    IntroState(SoundManager& sp, sf::RenderWindow& window);

    void resizeElements(sf::RenderWindow& window);
    void update(sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;

private:
    void animateLogo();
    void scrollText(sf::RenderWindow& window, sf::Time elapsed);

    SoundManager& soundPlayer;
    sf::Font font;
    TextScroll firstLine;
    TextScroll secondLine;
    LogoAnimation logoAnimation;
    sf::Sprite logoSprite;
    sf::Texture logoTexture;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    BackgroundHandler backgroundHandler;
    std::vector<std::string> backgroundFiles;
    sf::Clock clock;
    sf::Clock fadeClock;
    float fadeDuration;
    float pauseDuration;
    sf::Time totalElapsed;
    float firstLineSpeed;
    float secondLineSpeed;
    sf::Text instructionText; // Add this line
};

} // namespace SoftyPoker

#endif // INTRO_STATE_H

