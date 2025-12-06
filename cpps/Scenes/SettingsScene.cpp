//
// Created by M6XXY on 04/12/2025.
//

#include "SettingsScene.h"

#include <fstream>

void SettingsScene::draw(sf::RenderWindow& window) {
    menu.draw(window);
}

void SettingsScene::update(const sf::Vector2f& mousePos, bool mousePressed) {
    menu.update(mousePos, mousePressed);
}

void SettingsScene::menuState() {
    stateSettings = 1;
}

sf::Keyboard::Key SettingsScene::getKeyPressed(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        return event.key.code;
    }
}

void SettingsScene::saveKeybinds(Movement &movement) {
    // Open file stream
    std::ofstream file("../../keybinds.txt");
    //If file isnt open error
    if (!file.is_open()) {
        std::cerr << "CANNOT OPEN KEYBINDS.txt TO SAVE";
    }
    //save keys
    file << "p1Forward: "   << movement.keyToString(movement.p1Forward)   << "\n";
    file << "p1Left: "      << movement.keyToString(movement.p1Left)      << "\n";
    file << "p1Right: "     << movement.keyToString(movement.p1Right)     << "\n";
    file << "p1Back: "      << movement.keyToString(movement.p1Back)      << "\n";
    //close
    file.close();
}
