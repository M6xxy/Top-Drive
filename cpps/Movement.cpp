//
// Created by M6XXY on 16/11/2025.
// The purpose of this class is to control the movement of player sprites
//

#include "../header/movement.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

//Movement logic
MovementIntent Movement::captureInput() const {
    MovementIntent intent;

    // WASD Directions
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        intent.moveX -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        intent.moveX += 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        intent.moveY -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        intent.moveY += 1.0f;

    //Handbrake
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        intent.handbrake = true;

    return intent;

}
