#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SoundManager.h"
#include "GameState.h"
#include "TextScroll.h"
#include "LogoAnimation.h"
#include "BackgroundHandler.h"

namespace SoftyPoker {

class IntroState : public GameState {
public:
    IntroState(SoundManager& sp, sf::RenderWindow& window);
    void update(sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void resizeElements(sf::RenderWindow& window);

private:
    void animateLogo();  // Ensure this line is present
    void scrollText(sf::RenderWindow& window, sf::Time elapsed);  // Add this line to declare scrollText

    SoundManager& soundPlayer;
    sf::Font font;
    sf::Texture logoTexture;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::vector<std::string> backgroundFiles;
    TextScroll firstLine;
    TextScroll secondLine;
    LogoAnimation logoAnimation;
    BackgroundHandler backgroundHandler;
    sf::Sprite logoSprite;
    float horizontalOffset;
    sf::Clock clock;
    sf::Clock fadeClock;
    float fadeDuration;
    float firstLineSpeed;
    float secondLineSpeed;
};

} // namespace SoftyPoker

#endif // INTRO_STATE_H

