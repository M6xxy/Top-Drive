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
    // Check if mouse is over the button
    if (buttonRect.getGlobalBounds().contains(mousePos)) {
        buttonRect.setFillColor(hoverColour);

        // Call callback
        if (mousePressed && !isPressed) {
            if (callback) callback();
            isPressed = true;
        }
        else if (!mousePressed) {
            // Reset press
            isPressed = false;
        }

    } else {
        // Reset colour
        buttonRect.setFillColor(defaultColour);

        // Reset press state if mouse leaves
        if (!mousePressed) isPressed = false;
    }
}

void Button::setText(std::string text) {
    buttonText.setString(text);

    // Re-center text
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
                         textRect.top  + textRect.height / 2.0f);
}

