//
// Created by M6XXY on 23/11/2025.
//

#include "Button.h"

#include "SFML/Graphics/RenderWindow.hpp"

void Button::draw(sf::RenderWindow &window) {
    window.draw(buttonRect);
    window.draw(buttonText);
}

void Button::update(const sf::Vector2f mousePos, bool mousePressed) {
    //If mouse is in bounds
    if (buttonRect.getGlobalBounds().contains(mousePos)) {
        //Change colour on hover
        buttonRect.setFillColor(hoverColour);
        //If function exists run on click
        if (mousePressed && callback) {
            callback();
        }
    } else { // Reset colour
        buttonRect.setFillColor(defaultColour);
    }
}
