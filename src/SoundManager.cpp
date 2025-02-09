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
    // Check if music tracks are already initialized
    if (!musicTracks.empty()) {
        std::cout << "[Debug] Music already initialized" << std::endl;
        return;
    }

    std::cout << "[Debug] Initializing music" << std::endl;
    auto music1 = std::make_unique<sf::Music>();
    auto music2 = std::make_unique<sf::Music>();
    auto music3 = std::make_unique<sf::Music>();
    auto music4 = std::make_unique<sf::Music>();
    auto music5 = std::make_unique<sf::Music>();
    auto music6 = std::make_unique<sf::Music>(); // New music added

    try {
        if (!music1->openFromFile(getAssetPath("music/music1.ogg"))) {
            throw std::runtime_error("Failed to load music 1");
        }
        if (!music2->openFromFile(getAssetPath("music/music2.ogg"))) {
            throw std::runtime_error("Failed to load music 2");
        }
        if (!music3->openFromFile(getAssetPath("music/music3.ogg"))) {
            throw std::runtime_error("Failed to load music 3");
        }
        if (!music4->openFromFile(getAssetPath("music/music4.ogg"))) {
            throw std::runtime_error("Failed to load music 4");
        }
        if (!music5->openFromFile(getAssetPath("music/music5.ogg"))) {
            throw std::runtime_error("Failed to load music 5");
        }
        if (!music6->openFromFile(getAssetPath("music/music6.ogg"))) {
            throw std::runtime_error("Failed to load music 6");
        }

        musicTracks.push_back(std::move(music1));
        musicTracks.push_back(std::move(music2));
        musicTracks.push_back(std::move(music3));
        musicTracks.push_back(std::move(music4));
        musicTracks.push_back(std::move(music5));
        musicTracks.push_back(std::move(music6));

        for (const auto& music : musicTracks) {
            music->setVolume(100.0f); // Set volume for each music track
        }
        std::cout << "[Debug] Finished initializing music" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
        throw; // Rethrow the exception
    }
}

void SoundManager::playRandomBackgroundMusic() {
    std::cout << "[Debug] Attempting to play random background music" << std::endl;
    if (!musicTracks.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, static_cast<int>(musicTracks.size() - 1)); // Ensure the range is correct

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
