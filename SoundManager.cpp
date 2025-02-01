#include "SoundManager.h"

SoundManager::SoundManager() : currentMusic(nullptr) {
    // Initialize sound buffers and music tracks here if necessary
}

SoundManager::~SoundManager() {
    stopBackgroundMusic(); // Ensure music is stopped
}

void SoundManager::initializeAllSounds() {
    // Load all sound buffers and set them to the corresponding sounds
}

void SoundManager::playRandomBackgroundMusic() {
    // Logic to play a random music track
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
    else if (soundName == "prize") prizeSound.play();
    else if (soundName == "count") countSound.play();
    else if (soundName == "lose") loseSound.play();
    else if (soundName == "win") winSound.play();
}
