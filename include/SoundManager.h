#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <memory>
#include <vector>

class SoundManager {
public:
    ~SoundManager();
    void initializeAllSounds();
    void playRandomBackgroundMusic();
    void stopBackgroundMusic();
    void playSound(const std::string& soundName);

private:
    sf::Sound cardDealSound;
    sf::Sound heldSound;
    sf::Sound unheldSound;
    sf::Sound prizeSound;
    sf::Sound countSound;
    sf::Sound loseSound;
    sf::Sound winSound;
    std::vector<std::unique_ptr<sf::Music>> musicTracks;
    sf::Music* currentMusic = nullptr;
};

#endif // SOUNDMANAGER_H
