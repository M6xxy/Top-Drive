//
// Created by Carte on 27/11/2025.
//

#pragma once
#include "SFML/Graphics.hpp"
#include "Car.h"

class rpmGauge {

public:
    rpmGauge();

    // Call once per frame to update
    void update(const Car& car);

    //Draw rpm gauge
    void draw(sf::RenderWindow& window);

    // reposition gauge
    void setPosition(float x, float y);

    // toggle visibility
    void setVisible(bool visible);

private:
    bool m_visible = false;
    sf::Vector2f m_position;

    sf::Font m_font;
    sf::Text m_rpmText;

    // Horiziontal rpm gauge
    sf::RectangleShape m_backgroundBar;
    sf::RectangleShape m_barFill;

};