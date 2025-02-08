#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void initializeMusic();
    void playRandomBackgroundMusic();
    void initializeGameSounds();
    void playSound(const std::string& soundName);

private:
    std::vector<std::unique_ptr<sf::Music>> musicTracks;
    sf::Music* currentMusic;
    std::vector<sf::SoundBuffer> soundBuffers;
    sf::Sound cardDealSound, heldSound, unheldSound, prizeSound, countSound, loseSound, winSound;
};

#endif // SOUNDMANAGER_H
