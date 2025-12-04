//
// Created by M6XXY on 16/11/2025.
// The purpose of this class is to control the movement of player sprites
//

#include "../header/movement.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

//Movement logic
MovementIntent Movement::captureInput() const {
    MovementIntent intent;

    // Steering
    if (sf::Keyboard::isKeyPressed(p1Left))
        intent.steer -= 1.0f;
    if (sf::Keyboard::isKeyPressed(p1Right))
        intent.steer += 1.0f;

    if (sf::Keyboard::isKeyPressed(p1Forward))
        intent.throttle += 1.0f;
    if (sf::Keyboard::isKeyPressed(p1Back))
        intent.throttle -= 1.0f;

    //Handbrake
    if (sf::Keyboard::isKeyPressed(p1Handbrake))
        intent.handbrake = true;

    return intent;

}

sf::Keyboard::Key Movement::stringToKey(const std::string& keyStr) const {
    if (keyStr == "W") return sf::Keyboard::W;
    else if (keyStr == "A") return sf::Keyboard::A;
    else if (keyStr == "S") return sf::Keyboard::S;
    else if (keyStr == "D") return sf::Keyboard::D;
    else if (keyStr == "Space") return sf::Keyboard::Space;
    else if (keyStr == "Up") return sf::Keyboard::Up;
    else if (keyStr == "Down") return sf::Keyboard::Down;
    else if (keyStr == "Left") return sf::Keyboard::Left;
    else if (keyStr == "Right") return sf::Keyboard::Right;

    // Default to Unknown if the key is not recognized
    return sf::Keyboard::Unknown;
}

std::string Movement::keyToString(sf::Keyboard::Key key) {
    static const std::unordered_map<sf::Keyboard::Key, std::string> keyToStringMap = {
        {sf::Keyboard::A, "A"},
        {sf::Keyboard::B, "B"},
        {sf::Keyboard::C, "C"},
        {sf::Keyboard::D, "D"},
        {sf::Keyboard::E, "E"},
        {sf::Keyboard::F, "F"},
        {sf::Keyboard::G, "G"},
        {sf::Keyboard::H, "H"},
        {sf::Keyboard::I, "I"},
        {sf::Keyboard::J, "J"},
        {sf::Keyboard::K, "K"},
        {sf::Keyboard::L, "L"},
        {sf::Keyboard::M, "M"},
        {sf::Keyboard::N, "N"},
        {sf::Keyboard::O, "O"},
        {sf::Keyboard::P, "P"},
        {sf::Keyboard::Q, "Q"},
        {sf::Keyboard::R, "R"},
        {sf::Keyboard::S, "S"},
        {sf::Keyboard::T, "T"},
        {sf::Keyboard::U, "U"},
        {sf::Keyboard::V, "V"},
        {sf::Keyboard::W, "W"},
        {sf::Keyboard::X, "X"},
        {sf::Keyboard::Y, "Y"},
        {sf::Keyboard::Z, "Z"},
        {sf::Keyboard::Space, "Space"},
        {sf::Keyboard::Enter, "Enter"},
        {sf::Keyboard::Escape, "Escape"},
        {sf::Keyboard::Up, "Up"},
        {sf::Keyboard::Down, "Down"},
        {sf::Keyboard::Left, "Left"},
        {sf::Keyboard::Right, "Right"},
        {sf::Keyboard::F1, "F1"},
        {sf::Keyboard::F2, "F2"},
        {sf::Keyboard::F3, "F3"},
        {sf::Keyboard::F4, "F4"},
        {sf::Keyboard::F5, "F5"},
        {sf::Keyboard::F6, "F6"},
        {sf::Keyboard::F7, "F7"},
        {sf::Keyboard::F8, "F8"},
        {sf::Keyboard::F9, "F9"},
        {sf::Keyboard::F10, "F10"},
        {sf::Keyboard::F11, "F11"},
        {sf::Keyboard::F12, "F12"},
    };

    auto it = keyToStringMap.find(key);
    if (it != keyToStringMap.end()) {
        return it->second;
    }

    return "Unknown"; // Return "Unknown" for undefined keys
}

void Movement::loadKeyMap(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ERROR: CANNOT LOAD KEYBINDS" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file,line)) {
        //Declare Streams
        std::istringstream iss(line);
        std::string key,value;

        if (std::getline(iss,key,':') && std::getline(iss,value)) {
            //Trim whitespace characters
            key = key.substr(key.find_first_not_of(" \t"));
            value = value.substr(value.find_first_not_of(" \t"));

            //Store in list
            sf::Keyboard::Key mappedKey = stringToKey(value);
            KeybindVector.emplace_back(key, mappedKey);

            //Assign to action
            if (key == "p1Forward") {
                p1Forward = stringToKey(value);
            }
            else if (key == "p1Left") {
                p1Left = stringToKey(value);
            }
            else if (key == "p1Right") {
                p1Right = stringToKey(value);
            }
            else if (key == "p1Back") {
                p1Back = stringToKey(value);
            }
            else if (key == "p1Handbrake") {
                p1Handbrake = stringToKey(value);
            }
        }
    }
}

