//
// Created by M6XXY on 23/11/2025.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <functional>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include <functional>


namespace sf {
    class RenderWindow;
}

class Button {
public:
    Button(const std::string& text, sf::Vector2f size, sf::Vector2f position, sf::Font& font) {
        buttonRect.setSize(size);
        buttonRect.setPosition(position);
        buttonRect.setFillColor(defaultColour);

        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);

        //Center Text
        sf::FloatRect textRect = buttonText.getLocalBounds();
        buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
                                textRect.top + textRect.height / 2.0f);
        buttonText.setPosition(
            position.x + size.x / 2.0f,
            position.y + size.y / 2.0f
        );
    }
    void draw(sf::RenderWindow& window);

    void setCallback(std::function<void()> func) { callback = func;}

    void update(sf::Vector2f mousePos, bool mousePressed);;

    void setText(std::string text);
private:
    sf::RectangleShape buttonRect;
    sf::Text buttonText;
    sf::Color defaultColour = sf::Color::Cyan;
    sf::Color hoverColour = sf::Color::Blue;
    std::function<void()> callback;
    bool isPressed = false;
};



#endif //BUTTON_H
