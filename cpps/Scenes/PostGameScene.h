//
// Created by M6XXY on 07/12/2025.
//

#ifndef POSTGAMESCENE_H
#define POSTGAMESCENE_H

#include <iostream>

#include "../UI/Menu.h"
#include "SFML/Graphics/RenderWindow.hpp"

class PostGameScene {
public:
    int exit = 0;
    PostGameScene(sf::RenderWindow& window) {
        //Load Font
        if (!font.loadFromFile("../../assets/ARIAL.TTF")) {
            std::cerr << "ERROR: FAILED TO LOAD FONT";
        }

        //Top Screen Text
        winLossText.setFont(font);
        winLossText.setString("WINLOSSTEXT");
        //Center
        winLossText.setPosition(1920/2,300);


        //Return to Menu Button
        Button backButton("Back",sf::Vector2f(250,100),sf::Vector2f(1920/2 -125,800),font);
        backButton.setCallback([this]() { exit = 1;  });

        menu.addButton(backButton);
 }

    void draw(sf::RenderWindow &window);
    void update(const sf::Vector2f &mousePos, bool mousePressed);
    void loss();

    void win();

private:
    sf::Text winLossText;
    Menu menu;
    sf::Font font;
};



#endif //POSTGAMESCENE_H
