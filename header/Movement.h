// Created by Adrian CIs 16/11/2025
#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

struct MovementIntent {
    float throttle = 0.0f; // -1 Full Reverse , +1 Full Forward
    float steer = 0.0f; // -1 LEFT , +1 RIGHT
    bool handbrake = false;
};


class Movement {
public:
    Movement() = default;

    // Reads keyboard inputs and returns user input
    MovementIntent captureInput() const;
};
