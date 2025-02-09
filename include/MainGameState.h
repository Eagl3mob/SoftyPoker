#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include "GameState.h"
#include "SoundManager.h"

namespace SoftyPoker {
    class MainGameState : public GameState {
    public:
        MainGameState(SoundManager& sp, sf::RenderWindow& window, const std::string& backgroundPath);
        void update(sf::RenderWindow& window) override;
        void draw(sf::RenderWindow& window) override;
        void handleEvent(sf::Event& event, sf::RenderWindow& window) override;

    private:
        SoundManager& soundPlayer;
        sf::Clock clock;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
    };
}

#endif // MAINGAMESTATE_H
