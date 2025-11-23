//
// Created by M6XXY on 23/11/2025.
//

#include "MenuScene.h"

void MenuScene::draw(sf::RenderWindow& window) {
    menu.draw(window);
}

void MenuScene::update(const sf::Vector2f& mousePos, bool mousePressed) {
    menu.update(mousePos, mousePressed);
}

void MenuScene::menuState() {
    state = 1;
}


