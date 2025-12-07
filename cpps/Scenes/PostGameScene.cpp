//
// Created by M6XXY on 07/12/2025.
//

#include "PostGameScene.h"
void PostGameScene::draw(sf::RenderWindow& window) {
    window.draw(winLossText);
    menu.draw(window);
}

void PostGameScene::update(const sf::Vector2f& mousePos, bool mousePressed) {
    menu.update(mousePos, mousePressed);
}