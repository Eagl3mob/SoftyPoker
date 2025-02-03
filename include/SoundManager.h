#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <memory>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void initializeMusic();
    void playRandomBackgroundMusic();
    void initializeGameSounds();
    void playSound(const std::string& soundName);

    // Public sounds
    sf::Sound cardDealSound;
    sf::Sound heldSound;
    sf::Sound unheldSound;
    sf::Sound prizeSound;
    sf::Sound countSound;
    sf::Sound loseSound;
    sf::Sound winSound;

private:
    std::vector<std::unique_ptr<sf::Music>> musicTracks;
    sf::Music* currentMusic;
    std::vector<sf::SoundBuffer> soundBuffers;
};

#endif // SOUNDMANAGER_H
