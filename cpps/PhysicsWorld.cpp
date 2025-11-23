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

void PhysicsWorld::applyMovementIntent(b2Body* body, const MovementIntent& intent, float maxSpeedMetersPerSec) {

    if (!body) return;

    //  Standard Car Parameters
    const float acceleration = maxSpeedMetersPerSec * 2.0f; // m/s"
    const float turnSpeed = 2.5f; // Turn speed for full steer
    const float lateralFriction = 10.f; // friction booster to help sidewards drift

    // Get current velocity and orientation
    b2Vec2 vel = body->GetLinearVelocity();

    // Forward vector
    float angle = body->GetAngle();
    b2Vec2 forward(std::sin(angle), -std::cos(angle));

    // Simulate Tyre Friction
    b2Vec2 right(forward.y, -forward.x);
    float lateralSpeed = b2Dot(vel,right);
    b2Vec2 lateralVel = lateralSpeed * right;

    // Throttle / Brake

    float throttle = intent.throttle;
    if (std::fabs(throttle) > 0.01f) {
        // Add acceleration
        float scaler = throttle * acceleration * body->GetMass();
        b2Vec2 force = scaler * forward;
        body->ApplyForceToCenter(force, true);
    }

    // Cap Speed
    vel = body->GetLinearVelocity();
    float speed = vel.Length();
    if (speed > maxSpeedMetersPerSec) {
        vel *= maxSpeedMetersPerSec / speed;
        body->SetLinearVelocity(vel);
    }

    // Steering

    float steer = intent.steer;
    float desiredAngularVel = steer * turnSpeed;
    body->SetAngularVelocity(desiredAngularVel);

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



