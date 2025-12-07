//
// Created by Carte on 07/12/2025.
//

#include "../header/Sound/SoundController.h"
#include <algorithm>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

bool SoundController::init(const std::string& soundPath) {
    if (!m_buffer.loadFromFile(soundPath)) { // Check if u can load the soundfile from the speciifed path
        std::cerr << "Failed to load sound buffer from " << soundPath << "\n"; // Failed to load sound file
        m_loaded = false; // Sound isnt loaded
        return false;
    }

    m_sound.setBuffer(m_buffer);
    m_sound.setLoop(true);
    m_sound.setVolume(0.f); // Volume is controlled in update
    m_sound.setPitch(1.f);
    m_sound.setRelativeToListener(true); // 2D audio only so no 3d planning

    m_loaded = true;
    return true;
}

void SoundController::setEnabled(bool enabled) {
    m_enabled = enabled;
    if (!m_enabled && m_sound.getStatus() == sf::Sound::Playing) { // If the sound is not enabled but still playing. stop it
        m_sound.stop();
    }
}

void SoundController::update(float rpm, float idleRpm, float redline, float throttle, float dt) {
    if (!m_loaded || !m_enabled) return; // If sound isnt enabled or loaded dont update

    //silence rpm if below 800 rpm
    if (rpm < m_minRpmToActivate) {
        if (m_sound.getStatus() == sf::Sound::Playing) {
            m_sound.stop();
        }
        return;
    }

    // Start playing the sound if not already playing
    if (m_sound.getStatus() == sf::Sound::Playing) {
        m_sound.play();
    }

    // Clamp rpm range between min active rpm and the redline
    float baseRpm = std::max(m_minRpmToActivate, idleRpm);
    if (redline <= baseRpm) redline = baseRpm + 100.f;

    float clampedRpm = std::clamp(rpm, baseRpm, redline);

    // Normalize the value to be between 0 and 1
    float t = (clampedRpm - baseRpm) / (redline - baseRpm);
    t = std::clamp(t, 0.f, 1.f);

    // Pitch mapping for the audio
    float minPitch = 0.8f;
    float maxPitch = 2.f;
    float pitch = minPitch + t * (maxPitch - minPitch);

    m_sound.setPitch(pitch);

    float baseVolume = 25.f; // volume at min active rpm with zero throttle
    float rpmVolume = 45.f * t;

    float volume = baseVolume + rpmVolume;

    volume = std::clamp(volume, 0.f, 100.f);

    m_sound.setVolume(volume);

}



