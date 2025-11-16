// Created by Adrian CIs 16/11/2025
#pragma once
#include <SFML/Graphics.hpp>

class Movement {
public:
    Movement(sf::Sprite& shape, float speed);
    void update(float dt);
private:
    sf::Sprite& m_shape;
    float m_speed;
};