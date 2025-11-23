//
// Created by Carte on 20/11/2025.
//

#pragma once

#include <box2d/box2d.h>

struct MovementIntent;

class PhysicsWorld {
public:
    explicit PhysicsWorld(const b2Vec2& gravity = {0.f, 9.8f}, float scale = 30.f);

    void step(float dt);

    void applyMovementIntent(b2Body* body, const MovementIntent& intent, float maxSpeedMetersPerSec);

    // Unprocessed world access for map editing
    b2World& world();

    // Helper Functions
    float getScale() const;
    float toMeters(float pixels) const;
    float toPixels(float meters) const;

private:
    b2World m_world;
    float m_scale;
};