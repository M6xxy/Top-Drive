//
// Created by M6XXY on 04/12/2025.
//

#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H
#include <iostream>

#include "Movement.h"
#include "../Global/Global.h"
#include "../UI/Menu.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Sound/SoundController.h"


class Movement;

class SettingsScene {
public:
    int stateSettings = 1;
    bool waitingForForwardKey = false;
    bool waitingForLeftKey = false;
    bool waitingForRightKey = false;
    bool waitingForBackKey = false;
    SettingsScene(sf::RenderWindow& window, Movement& movementRef, Global &gv) {
        //Load Font
        if (!font.loadFromFile("../../assets/ARIAL.TTF")) {
            std::cerr << "ERROR: FAILED TO LOAD FONT";
        }
        //Init Buttons
        //SSettings Button
        Button playButton("RESOLUTION : 1920 x 1080", sf::Vector2f(250, 75),
                          sf::Vector2f(gv.resX / 2 - 125, 175), font);
        playButton.setCallback([this, &gv, &window]() {
            if (gv.resX == 1920 && gv.resY == 1080) {
                gv.resX = 800;
                gv.resY = 800;
            } else {
                gv.resX = 1920;
                gv.resY = 1080;
            }
            // Re-Center
            window.create(sf::VideoMode(gv.resX, gv.resY), "Top Drive", sf::Style::Default);
            window.setView(window.getDefaultView());
            menu.setText(0, "RESOLUTION : " + std::to_string(gv.resX) + " x " + std::to_string(gv.resY));
        });

        Button forwardButton("Forward : " + movementRef.keyToString(movementRef.KeybindVector.at(0).second),
                             sf::Vector2f(250, 50), sf::Vector2f(gv.resX  / 2 - 125, 290), font);
        forwardButton.setCallback([this]() { waitingForForwardKey = true; });

        Button downButton("Down : " + movementRef.keyToString(movementRef.KeybindVector.at(3).second),
                          sf::Vector2f(250, 50), sf::Vector2f(gv.resX  / 2 - 125, 350), font);
        downButton.setCallback([this]() { waitingForBackKey = true; });

        Button LeftButton("Left : " + movementRef.keyToString(movementRef.KeybindVector.at(1).second),
                          sf::Vector2f(250, 50), sf::Vector2f(gv.resX  / 2 - 125, 410), font);
        LeftButton.setCallback([this]() { waitingForLeftKey = true; });

        Button RightButton("Right : " + movementRef.keyToString(movementRef.KeybindVector.at(2).second),
                           sf::Vector2f(250, 50), sf::Vector2f(gv.resX  / 2 - 125, 470), font);
        RightButton.setCallback([this]() { waitingForRightKey = true; });

        //Back Button
        Button backButton("Back", sf::Vector2f(250, 75), sf::Vector2f(gv.resX / 2 - 125, 675), font);
        backButton.setCallback([this]() { stateSettings = 0; });


        //Add Buttons
        menu.addButton(playButton);
        menu.addButton(forwardButton);
        menu.addButton(downButton);
        menu.addButton(LeftButton);
        menu.addButton(RightButton);
        menu.addButton(backButton);
    }

    void draw(sf::RenderWindow &window);
    sf::Keyboard::Key getKeyPressed(sf::Event &event);

    void saveKeybinds(Movement &movement);

    void update(const sf::Vector2f &mousePos, bool mousePressed);
    Menu menu;
private:

    sf::Font font;
    void menuState();



    sf::Keyboard::Key getKeybinds(sf::Event &event);
};



#endif //SETTINGSSCENE_H
