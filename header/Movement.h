// Created by Adrian CIs 16/11/2025
#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

struct MovementIntent {
    float throttle = 0.0f; // -1 Full Reverse , +1 Full Forward
    float steer = 0.0f; // -1 LEFT , +1 RIGHT
    bool handbrake = false;
};


class Movement {
public:
    std::vector<std::pair<std::string, sf::Keyboard::Key>> KeybindVector;

    sf::Keyboard::Key p1Forward;
    sf::Keyboard::Key p1Left;
    sf::Keyboard::Key p1Right;
    sf::Keyboard::Key p1Back;
    sf::Keyboard::Key p1Handbrake;

    Movement(const std::string& filename) {
        loadKeyMap(filename); // Load key mappings in const
    }

    void loadKeyMap(const std::string& filename);

    bool controllerConntected() const {
        return sf::Joystick::isConnected(0); // Check if controller is connected to #0, It should always be one since there is only 1 player
    }

    // Reads keyboard inputs and returns user input
    MovementIntent captureInput() const;

    sf::Keyboard::Key stringToKey(const std::string &keyStr) const;

    std::string keyToString(sf::Keyboard::Key key);
private:
};
