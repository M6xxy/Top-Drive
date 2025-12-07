//
// Created by M6XXY on 07/12/2025.
//

#include "PostGameScene.h"
void PostGameScene::draw(sf::RenderWindow& window) {
    sf::FloatRect bounds = winLossText.getLocalBounds();
    winLossText.setOrigin(bounds.left + bounds.width / 2,
                  bounds.top  + bounds.height / 2);
    window.draw(winLossText);
    menu.draw(window);
}

void PostGameScene::update(const sf::Vector2f& mousePos, bool mousePressed) {
    menu.update(mousePos, mousePressed);
}

void PostGameScene::loss() {
    winLossText.setString("YOU LOST!");
}

void PostGameScene::win() {
    winLossText.setString("YOU WON!");
}
