//
// Created by M6XXY on 23/11/2025.
//

#include "Menu.h"

#include "SFML/Graphics/RenderWindow.hpp"

void Menu::addButton(Button button) {
    buttonList.push_back(button);
}

void Menu::draw(sf::RenderWindow& window) {
    for (auto& button : buttonList) {
        button.draw(window);
    }
}

void Menu::update(const sf::Vector2f mousePos, bool mousePressed) {
    for (auto& button : buttonList) {
        button.update(mousePos,mousePressed);
    }
}

void Menu::setText(int pos,std::string text) {
    buttonList.at(pos).setText(text);
}
