//
// Created by M6XXY on 04/12/2025.
//

#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H
#include <iostream>

#include "Movement.h"
#include "../UI/Menu.h"
#include "SFML/Graphics/RenderWindow.hpp"


class Movement;

class SettingsScene {
public:
    int stateSettings = 1;
    SettingsScene(sf::RenderWindow& window, Movement& movementRef) {
        //Load Font
        if (!font.loadFromFile("../../assets/ARIAL.TTF")) {
            std::cerr << "ERROR: FAILED TO LOAD FONT";

        }
        //Init Buttons
        //SSettings Button
        Button playButton("SETTINGS",sf::Vector2f(250,75),sf::Vector2f(300,175),font);
        playButton.setCallback([this]() { ; });

        Button forwardButton("Forward : " + movementRef.keyToString(movementRef.KeybindVector.at(0).second) ,sf::Vector2f(250,50),sf::Vector2f(300,290),font);
        forwardButton.setCallback([this]() { ; });

        Button downButton("Down : " + movementRef.keyToString(movementRef.KeybindVector.at(3).second),sf::Vector2f(250,50),sf::Vector2f(300,350),font);
        downButton.setCallback([this]() { ; });

        Button LeftButton("Left : "+ movementRef.keyToString(movementRef.KeybindVector.at(1).second),sf::Vector2f(250,50),sf::Vector2f(300,410),font);
        LeftButton.setCallback([this]() { ; });

        Button RightButton("Right : "+ movementRef.keyToString(movementRef.KeybindVector.at(2).second),sf::Vector2f(250,50),sf::Vector2f(300,470),font);
        RightButton.setCallback([this]() { ; });


        //Back Button
        Button backButton("Back",sf::Vector2f(250,75),sf::Vector2f(300,675),font);
        backButton.setCallback([this]() { stateSettings = 0;  });


        //Add Buttons
        menu.addButton(playButton);
        menu.addButton(forwardButton);
        menu.addButton(downButton);
        menu.addButton(LeftButton);
        menu.addButton(RightButton);
        menu.addButton(backButton);

    }
    void draw(sf::RenderWindow &window);

    void update(const sf::Vector2f &mousePos, bool mousePressed);
private:
    Menu menu;
    sf::Font font;
    void menuState();
    void getKeybinds();
};



#endif //SETTINGSSCENE_H
