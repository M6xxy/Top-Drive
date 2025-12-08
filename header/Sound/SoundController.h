//
// Created by Carte on 07/12/2025.
//

#pragma once

#include <SFML/Audio.hpp>
#include <string>

class SoundController {

public:
    SoundController() = default;

    // Load Engine sound
    bool init(const std::string& soundPath);

    // rpm = current engine rpm
    // idle rpm = current engine idle rpm
    // redline = engines max rpm
    // throttle = Is the user on the throttle
    void update(float rpm, float idleRpm, float redline, float throttle, float dt);

    float getVolume() const {
        return m_sound.getVolume();
    }

    void setEnabled(bool enabled);
    bool isEnabled() const { return m_enabled; }

private:
    sf::SoundBuffer m_buffer;
    sf::Sound m_sound;
    bool m_enabled = true; // Enable the sound
    bool m_loaded = false; // This will be set in the handler so we can modify it in the future for diffrent cars / electric etc

    const float m_minRpmToActivate = 955.f; // No sound when rpm is below the set value
};