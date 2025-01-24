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

    // Getter methods to access private sounds
    sf::Sound& getCardDealSound() { return cardDealSound; }
    sf::Sound& getHeldSound() { return heldSound; }
    sf::Sound& getUnheldSound() { return unheldSound; }
    sf::Sound& getPrizeSound() { return prizeSound; }
    sf::Sound& getCountSound() { return countSound; }
    sf::Sound& getLoseSound() { return loseSound; }
    sf::Sound& getWinSound() { return winSound; }

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

