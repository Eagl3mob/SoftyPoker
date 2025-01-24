#include "SoundManager.h"
#include <iostream>
#include <random>  // Ensure this header is included

void SoundManager::initializeAllSounds() {
    std::vector<std::pair<std::string, sf::Sound&>> soundFiles = {
        {"D:/Programming/Projects/Assets/sounds/cardDeal.wav", cardDealSound},
        {"D:/Programming/Projects/Assets/sounds/held.wav", heldSound},
        {"D:/Programming/Projects/Assets/sounds/unheld.wav", unheldSound},
        {"D:/Programming/Projects/Assets/sounds/prize.wav", prizeSound},
        {"D:/Programming/Projects/Assets/sounds/count.wav", countSound},
        {"D:/Programming/Projects/Assets/sounds/lose.wav", loseSound},
        {"D:/Programming/Projects/Assets/sounds/win.wav", winSound}
    };

    std::vector<sf::SoundBuffer> buffers(soundFiles.size());
    for (size_t i = 0; i < soundFiles.size(); i++) {
        if (!buffers[i].loadFromFile(soundFiles[i].first)) {
            std::cerr << "Failed to load sound: " << soundFiles[i].first << std::endl;
            throw std::runtime_error("Failed to initialize sound.");
        }
        soundFiles[i].second.setBuffer(buffers[i]);
        soundFiles[i].second.setVolume(100.0f); // Set volume for each sound
        std::cout << "[Debug] Sound initialized: " << soundFiles[i].first << std::endl;
    }

    // Load background music tracks
    auto music1 = std::make_unique<sf::Music>();
    auto music2 = std::make_unique<sf::Music>();
    auto music3 = std::make_unique<sf::Music>();
    auto music4 = std::make_unique<sf::Music>();
    auto music5 = std::make_unique<sf::Music>();

    if (!music1->openFromFile("D:/Programming/Projects/Assets/music/music1.ogg")) {
        throw std::runtime_error("Failed to load music 1");
    }
    if (!music2->openFromFile("D:/Programming/Projects/Assets/music/music2.ogg")) {
        throw std::runtime_error("Failed to load music 2");
    }
    if (!music3->openFromFile("D:/Programming/Projects/Assets/music/music3.ogg")) {
        throw std::runtime_error("Failed to load music 3");
    }
    if (!music4->openFromFile("D:/Programming/Projects/Assets/music/music4.ogg")) {
        throw std::runtime_error("Failed to load music 4");
    }
    if (!music5->openFromFile("D:/Programming/Projects/Assets/music/music5.ogg")) {
        throw std::runtime_error("Failed to load music 5");
    }

    musicTracks.push_back(std::move(music1));
    musicTracks.push_back(std::move(music2));
    musicTracks.push_back(std::move(music3));
    musicTracks.push_back(std::move(music4));
    musicTracks.push_back(std::move(music5));

    for (const auto& music : musicTracks) {
        music->setVolume(100.0f); // Set volume for each music track
    }
}

void SoundManager::playRandomBackgroundMusic() {
    if (!musicTracks.empty()) {
        // Select a random music track
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, musicTracks.size() - 1);

        currentMusic = musicTracks[distr(gen)].get();
        currentMusic->setLoop(true);
        currentMusic->play();
        std::cout << "[Debug] Playing random background music" << std::endl;
    }
}

void SoundManager::stopBackgroundMusic() {
    if (currentMusic != nullptr) {
        currentMusic->stop();
        currentMusic = nullptr;
    }
}

void SoundManager::playSound(const std::string& soundName) {
    std::cout << "[Debug] Playing sound: " << soundName << std::endl;
    if (soundName == "cardDeal") cardDealSound.play();
    else if (soundName == "held") heldSound.play();
    else if (soundName == "unheld") unheldSound.play();
    else if (soundName == "prize") prizeSound.play();
    else if (soundName == "count") countSound.play();
    else if (soundName == "lose") loseSound.play();
    else if (soundName == "win") winSound.play();
}

SoundManager::~SoundManager() {
    stopBackgroundMusic(); // Ensure music is stopped
}
