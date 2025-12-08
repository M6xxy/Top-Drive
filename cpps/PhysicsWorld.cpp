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

    if (!body) return; // If the car doesen't exist dont continue

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
    float lateralSpeed = b2Dot(vel,right); // Get the cars current lateral speed
    b2Vec2 lateralVel = lateralSpeed * right;

    // Throttle / Brake

    float throttle = intent.throttle; // Is the player on the gas?
    if (std::fabs(throttle) > 0.01f) { // If the user is on the gas add acceleration
        // Add acceleration
        float scaler = throttle * acceleration * body->GetMass(); // Depending on how much throttle is being used times it by acceleration of the car and the mass of the car
        b2Vec2 force = scaler * forward;
        body->ApplyForceToCenter(force, true); // Apply the accelration to the car
    }

    // Cap Speed
    vel = body->GetLinearVelocity(); // Get the cars current velocity
    float speed = vel.Length(); // get the speed from velocity
    if (speed > maxSpeedMetersPerSec) { // If the speed if faster than the allowed max speed
        vel *= maxSpeedMetersPerSec / speed; // Slow the velocity down
        body->SetLinearVelocity(vel); // Apply the modified forces to the car
    }

    // Steering

    float steer = intent.steer; // Is the player steering?
    float desiredAngularVel = steer * turnSpeed; // Steering speed = if the users turning take into account the set turn speed
    body->SetAngularVelocity(desiredAngularVel); // Apply the desired angular velocity to the car

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



