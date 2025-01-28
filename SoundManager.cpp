#include "SoundManager.h"
#include <iostream>
#include <random>

SoundManager::SoundManager() {
    // Default constructor implementation (if needed)
}

void SoundManager::initializeAllSounds() {
    const std::vector<std::pair<std::string, sf::Sound*>> soundFiles = {
        {"Assets/sounds/cardDeal.wav", &cardDealSound},
        {"Assets/sounds/held.wav", &heldSound},
        {"Assets/sounds/unheld.wav", &unheldSound},
        {"Assets/sounds/count.wav", &countSound},
        {"Assets/sounds/lose.wav", &loseSound},
        {"Assets/sounds/win.wav", &winSound},
        {"Assets/sounds/prize.wav", &prizeSound} // Include prizeSound
    };

    soundBuffers.resize(soundFiles.size());
    for (size_t i = 0; i < soundFiles.size(); ++i) {
        if (!soundBuffers[i].loadFromFile(soundFiles[i].first)) {
            throw std::runtime_error("Failed to initialize sound: " + soundFiles[i].first);
        }
        soundFiles[i].second->setBuffer(soundBuffers[i]);
        soundFiles[i].second->setVolume(100.0f);
    }

    // Load background music tracks
    loadMusic("Assets/music/music1.ogg");
    loadMusic("Assets/music/music2.ogg");
    loadMusic("Assets/music/music3.ogg");
    loadMusic("Assets/music/music4.ogg");
    loadMusic("Assets/music/music5.ogg");

    for (const auto& music : musicTracks) {
        music->setVolume(100.0f); // Set volume for each music track
    }
}

void SoundManager::loadMusic(const std::string& filepath) {
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filepath)) {
        throw std::runtime_error("Failed to load music: " + filepath);
    }
    musicTracks.push_back(std::move(music));
}

void SoundManager::playRandomBackgroundMusic() {
    if (!musicTracks.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, musicTracks.size() - 1);

        currentMusic = musicTracks[distr(gen)].get();
        currentMusic->setLoop(true);
        currentMusic->play();
    }
}

void SoundManager::stopBackgroundMusic() {
    if (currentMusic != nullptr) {
        currentMusic->stop();
        currentMusic = nullptr;
    }
}

void SoundManager::playSound(const std::string& soundName) {
    if (soundName == "cardDeal") cardDealSound.play();
    else if (soundName == "held") heldSound.play();
    else if (soundName == "unheld") unheldSound.play();
    else if (soundName == "count") countSound.play();
    else if (soundName == "lose") loseSound.play();
    else if (soundName == "win") winSound.play();
    else if (soundName == "prize") prizeSound.play(); // Use prizeSound
}

SoundManager::~SoundManager() {
    stopBackgroundMusic();
}
