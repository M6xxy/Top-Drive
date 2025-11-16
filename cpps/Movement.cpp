//
// Created by M6XXY on 16/11/2025.
//

#include "../header/movement.h"


// Constructor
Movement::Movement(sf::Sprite &shape, float speed) :
    m_shape(shape), // Initialises Shape
    m_speed(speed) // Initialise speed
{}

//Movement logic
void Movement::update(float dt) {
    //Movement Vector
    sf::Vector2f move(0.f,0.f);

    //W
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // Up
        move.y -= m_speed * dt;
    //S
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Down
        move.y += m_speed * dt;

    //A
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Left
        move.x -= m_speed * dt;

    //D
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Right
        move.x += m_speed * dt;

    m_shape.move(move);
}

