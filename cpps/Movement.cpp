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
    if (keyStr == "A") return sf::Keyboard::A;
    else if (keyStr == "B") return sf::Keyboard::B;
    else if (keyStr == "C") return sf::Keyboard::C;
    else if (keyStr == "D") return sf::Keyboard::D;
    else if (keyStr == "E") return sf::Keyboard::E;
    else if (keyStr == "F") return sf::Keyboard::F;
    else if (keyStr == "G") return sf::Keyboard::G;
    else if (keyStr == "H") return sf::Keyboard::H;
    else if (keyStr == "I") return sf::Keyboard::I;
    else if (keyStr == "J") return sf::Keyboard::J;
    else if (keyStr == "K") return sf::Keyboard::K;
    else if (keyStr == "L") return sf::Keyboard::L;
    else if (keyStr == "M") return sf::Keyboard::M;
    else if (keyStr == "N") return sf::Keyboard::N;
    else if (keyStr == "O") return sf::Keyboard::O;
    else if (keyStr == "P") return sf::Keyboard::P;
    else if (keyStr == "Q") return sf::Keyboard::Q;
    else if (keyStr == "R") return sf::Keyboard::R;
    else if (keyStr == "S") return sf::Keyboard::S;
    else if (keyStr == "T") return sf::Keyboard::T;
    else if (keyStr == "U") return sf::Keyboard::U;
    else if (keyStr == "V") return sf::Keyboard::V;
    else if (keyStr == "W") return sf::Keyboard::W;
    else if (keyStr == "X") return sf::Keyboard::X;
    else if (keyStr == "Y") return sf::Keyboard::Y;
    else if (keyStr == "Z") return sf::Keyboard::Z;
    else if (keyStr == "Space") return sf::Keyboard::Space;
    else if (keyStr == "Enter") return sf::Keyboard::Enter;
    else if (keyStr == "Escape") return sf::Keyboard::Escape;
    else if (keyStr == "Up") return sf::Keyboard::Up;
    else if (keyStr == "Down") return sf::Keyboard::Down;
    else if (keyStr == "Left") return sf::Keyboard::Left;
    else if (keyStr == "Right") return sf::Keyboard::Right;
    else if (keyStr == "F1") return sf::Keyboard::F1;
    else if (keyStr == "F2") return sf::Keyboard::F2;
    else if (keyStr == "F3") return sf::Keyboard::F3;
    else if (keyStr == "F4") return sf::Keyboard::F4;
    else if (keyStr == "F5") return sf::Keyboard::F5;
    else if (keyStr == "F6") return sf::Keyboard::F6;
    else if (keyStr == "F7") return sf::Keyboard::F7;
    else if (keyStr == "F8") return sf::Keyboard::F8;
    else if (keyStr == "F9") return sf::Keyboard::F9;
    else if (keyStr == "F10") return sf::Keyboard::F10;
    else if (keyStr == "F11") return sf::Keyboard::F11;
    else if (keyStr == "F12") return sf::Keyboard::F12;

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

