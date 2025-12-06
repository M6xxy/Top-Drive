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
        isPressed = true;

       if (!mousePressed && isPressed) {
           isPressed = false;
       }
    } else { // Reset colour
        buttonRect.setFillColor(defaultColour);
    }
}

void Button::setText(std::string text) {
    buttonText.setString(text);

    // Re-center text
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
                         textRect.top  + textRect.height / 2.0f);
}

