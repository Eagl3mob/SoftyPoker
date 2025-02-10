#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include "GameState.h"
#include "SoundManager.h"
#include "ButtonHandle.h"

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
        ButtonHandle buttonHandle;

        void startGame();
        void bet();
        void deal();
        void collect();
        void enterGamblingState();
        void guessSmall();
        void guessHigh();
        void holdCard(int cardIndex);
    };
}

#endif // MAINGAMESTATE_H

