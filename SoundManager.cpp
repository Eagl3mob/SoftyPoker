#include "SoundManager.h"
#include "Utility.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>

SoundManager::SoundManager() {
    // Initialization here
}

SoundManager::~SoundManager() {
    // Cleanup here
}


void SoundManager::initializeMusic() {
    std::cout << "[Debug] Initializing music" << std::endl;
    auto music1 = std::make_unique<sf::Music>();
    auto music2 = std::make_unique<sf::Music>();
    auto music3 = std::make_unique<sf::Music>();
    auto music4 = std::make_unique<sf::Music>();
    auto music5 = std::make_unique<sf::Music>();

    if (!music1->openFromFile(getAssetPath("music/music1.ogg"))) {
        std::cerr << "[Error] Failed to load music 1" << std::endl;
        throw std::runtime_error("Failed to load music 1");
    }
    if (!music2->openFromFile(getAssetPath("music/music2.ogg"))) {
        std::cerr << "[Error] Failed to load music 2" << std::endl;
        throw std::runtime_error("Failed to load music 2");
    }
    if (!music3->openFromFile(getAssetPath("music/music3.ogg"))) {
        std::cerr << "[Error] Failed to load music 3" << std::endl;
        throw std::runtime_error("Failed to load music 3");
    }
    if (!music4->openFromFile(getAssetPath("music/music4.ogg"))) {
        std::cerr << "[Error] Failed to load music 4" << std::endl;
        throw std::runtime_error("Failed to load music 4");
    }
    if (!music5->openFromFile(getAssetPath("music/music5.ogg"))) {
        std::cerr << "[Error] Failed to load music 5" << std::endl;
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
    std::cout << "[Debug] Finished initializing music" << std::endl;
}



void SoundManager::playRandomBackgroundMusic() {
    std::cout << "[Debug] Attempting to play random background music" << std::endl;
    if (!musicTracks.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, musicTracks.size() - 1);

        size_t trackIndex = distr(gen);
        currentMusic = musicTracks[trackIndex].get();

        // Debug output for selected track
        std::cout << "[Debug] Selected track index: " << trackIndex << std::endl;
        std::cout << "[Debug] Music track at index: " << musicTracks[trackIndex].get() << std::endl;

        if (currentMusic) {
            currentMusic->stop(); // Ensure any previously playing music is stopped
            currentMusic->setLoop(true);
            currentMusic->play();
            std::cout << "[Debug] Playing random background music" << std::endl;
        } else {
            std::cerr << "[Error] currentMusic is null" << std::endl;
        }
    } else {
        std::cerr << "[Error] No music tracks available" << std::endl;
    }
}







void SoundManager::initializeGameSounds() {
    std::vector<std::pair<std::string, sf::Sound&>> soundFiles = {
        {getAssetPath("sounds/deal.wav"), cardDealSound},
        {getAssetPath("sounds/hold.wav"), heldSound},
        {getAssetPath("sounds/unheld.wav"), unheldSound},
        {getAssetPath("sounds/prize.wav"), prizeSound},
        {getAssetPath("sounds/count.wav"), countSound},
        {getAssetPath("sounds/lose.wav"), loseSound},
        {getAssetPath("sounds/win.wav"), winSound}
    };

    soundBuffers.resize(soundFiles.size());
    for (size_t i = 0; i < soundFiles.size(); ++i) {
        if (!soundBuffers[i].loadFromFile(soundFiles[i].first)) {
            std::cerr << "Failed to load sound: " << soundFiles[i].first << std::endl;
            throw std::runtime_error("Failed to initialize sound.");
        }
        soundFiles[i].second.setBuffer(soundBuffers[i]);
        soundFiles[i].second.setVolume(100.0f); // Set volume for each sound
        std::cout << "[Debug] Sound initialized: " << soundFiles[i].first << std::endl;
    }
}

void SoundManager::playSound(const std::string& soundName) {
    if (soundName == "deal") {
        cardDealSound.play();
    } else if (soundName == "hold") {
        heldSound.play();
    } else if (soundName == "unhold") {
        unheldSound.play();
    } else if (soundName == "prize") {
        prizeSound.play();
    } else if (soundName == "count") {
        countSound.play();
    } else if (soundName == "lose") {
        loseSound.play();
    } else if (soundName == "win") {
        winSound.play();
    } else {
        std::cerr << "[Error] Unknown sound name: " << soundName << std::endl;
    }
}
