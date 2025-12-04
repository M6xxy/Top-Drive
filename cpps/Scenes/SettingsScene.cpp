//
// Created by M6XXY on 04/12/2025.
//

#include "SettingsScene.h"

void SettingsScene::draw(sf::RenderWindow& window) {
    menu.draw(window);
}

void SettingsScene::update(const sf::Vector2f& mousePos, bool mousePressed) {
    menu.update(mousePos, mousePressed);
}

void SettingsScene::menuState() {
    stateSettings = 1;
}

void SettingsScene::getKeybinds() {

}
