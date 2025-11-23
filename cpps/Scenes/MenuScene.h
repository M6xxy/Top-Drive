//
// Created by M6XXY on 23/11/2025.
//

#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <iostream>

#include "../UI/Menu.h"
#include "SFML/Graphics/RenderWindow.hpp"


class MenuScene {
public:
    int state = 0;
    MenuScene(sf::RenderWindow& window) {
        //Load Font
        if (!font.loadFromFile("../../assets/ARIAL.TTF")) {
            std::cerr << "ERROR: FAILED TO LOAD FONT";

        }
        //Init Buttons
        //Play Button
        Button playButton("Play",sf::Vector2f(250,75),sf::Vector2f(300,175),font);
        playButton.setCallback([this]() { state = 1; });

        //Quit Button
        Button quitButton("Quit",sf::Vector2f(250,75),sf::Vector2f(300,275),font);
        quitButton.setCallback([this]() { exit(0); });

        //Add Buttons
        menu.addButton(playButton);
        menu.addButton(quitButton);

    }
    void draw(sf::RenderWindow &window);

    void update(const sf::Vector2f &mousePos, bool mousePressed);
private:
    Menu menu;
    sf::Font font;
    void menuState();

};



#endif //MENUSCENE_H
