// Created by Adrian CIs 16/11/2025
#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

struct MovementIntent {
    float moveX = 0.0f; // -1 LEFT , +1 RIGHT
    float moveY = 0.0f; // -1 UP , +1 DOWN
    bool handbrake = false;
};


class Movement {
public:
    Movement() = default;

    // Reads keyboard inputs and returns user input
    MovementIntent captureInput() const;
};
