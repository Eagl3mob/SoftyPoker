#include "StateManager.h"
#include "ControlManager.h"
#include "SoundManager.h"
#include "IntroState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SoftyPoker");
    StateManager stateManager;
    ControlManager controlManager(stateManager);
    SoundManager soundManager;

    soundManager.initializeMusic();
    auto introState = std::make_unique<SoftyPoker::IntroState>(soundManager, window);
    stateManager.addState("Intro", std::move(introState));
    stateManager.switchToState("Intro");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            controlManager.handleInput(event, window);
        }

        stateManager.update(window);
        stateManager.draw(window);
    }

    return 0;
}
