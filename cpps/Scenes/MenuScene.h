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
    int state = 1;
    int stateSettings = 0;
    MenuScene(sf::RenderWindow& window) {
        //Load Font
        if (!font.loadFromFile("../../assets/ARIAL.TTF")) {
            std::cerr << "ERROR: FAILED TO LOAD FONT";

        }
        //Init Buttons
        //Play Button
        Button playButton("Play",sf::Vector2f(250,75),sf::Vector2f(1920/2 - 125,275),font);
        playButton.setCallback([this]() { state = 2; });

        //Button Settings
        //Settings Button
        Button settingsButton("Settings",sf::Vector2f(250,75),sf::Vector2f(1920/2 - 125,375),font);
        settingsButton.setCallback([this]() { stateSettings = 1; });

        //Quit Button
        Button quitButton("Quit",sf::Vector2f(250,75),sf::Vector2f(1920/2 - 125,475),font);
        quitButton.setCallback([this]() {
            std::cout << "Quit button clicked, exiting...\n";
            exit(0);
        });

        //Add Buttons
        menu.addButton(playButton);
        menu.addButton(settingsButton);
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
