// Created by Adrian CIs 16/11/2025
#pragma once
#include <SFML/Graphics.hpp>

class Movement {
public:
    Movement(sf::CircleShape& shape, float speed);
    void update(float dt);
private:
    sf::CircleShape& m_shape;
    float m_speed;
};