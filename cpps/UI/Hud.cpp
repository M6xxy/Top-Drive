//
// Created by M6XXY on 07/12/2025.
//

#include "Hud.h"

#include <iostream>

#include "SFML/Graphics.hpp"
Hud::Hud() {
    if (!font.loadFromFile("../../assets/ARIAL.TTF")) {
        std::cerr << "ERROR CANT LOAD FONT FOR HUD";
    }
}
void Hud::display(CheckpointHandler &checkpointHandler, sf::RenderWindow &window) {

    lapText.setFont(font);
    lapText.setString("LAP X/X");
    lapText.setCharacterSize(25);
    lapText.setPosition(50,150);


    checkPointText.setFont(font);
    checkPointText.setString("Checkpoint X/X");
    checkPointText.setCharacterSize(25);
    checkPointText.setPosition(50,200);
}

void Hud::update(CheckpointHandler &ch, sf::RenderWindow &window) {

    if (ch.currCheckpoint == 0 && ch.lapCount > 0) {
        lcurrCheckpoint = ch.totalCheckpoints -1;
    } else {
        lcurrCheckpoint = ch.currCheckpoint;
    }

    lapText.setString("LAP " + std::to_string(ch.lapCount) + "/3");
    checkPointText.setString("Checkpoint " + std::to_string(lcurrCheckpoint) + "/" + std::to_string(ch.totalCheckpoints-1));
    window.draw(lapText);
    window.draw(checkPointText);
}

