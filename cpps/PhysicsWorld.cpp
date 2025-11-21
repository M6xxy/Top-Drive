//
// Created by Carte on 20/11/2025.
//

#include "../header/PhysicsWorld.h"
#include "../header/Movement.h"
#include <cmath>

PhysicsWorld::PhysicsWorld(const b2Vec2& gravity, float scale) : m_world(gravity), m_scale(scale) {}

void PhysicsWorld::step(float dt) {
    m_world.Step(dt, 8,3);
}

void PhysicsWorld::applyMovementIntent(b2Body* body, const MovementIntent& intent, float speedMetersPerSec) {

    if (!body) return;

    // Direction based on intent
    b2Vec2 dir(intent.moveX, intent.moveY);

    // Normalize input
    float lenSq = dir.x * dir.x + dir.y * dir.y;
    if (lenSq > 0.0001f) {
        float len = sqrtf(lenSq);
        dir.x /= len;
        dir.y /= len;
    }

    // Speed in meters / seconds
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x += dir.x * speedMetersPerSec;
    vel.y += dir.y * speedMetersPerSec;

    body->SetLinearVelocity(vel);

    if (intent.handbrake) {

    }

}

b2World& PhysicsWorld::world() {
    return m_world;
}

float PhysicsWorld::getScale() const {
    return m_scale;
}

float PhysicsWorld::toMeters(float pixels) const {
    return pixels / m_scale;
}

float PhysicsWorld::toPixels(float meters) const {
    return meters * m_scale;
}



