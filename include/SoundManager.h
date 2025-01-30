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

    void initializeAllSounds();
    void playRandomBackgroundMusic();
    void stopBackgroundMusic();
    void playSound(const std::string& soundName);

    // Make sounds public
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
};

#endif // SOUNDMANAGER_H
