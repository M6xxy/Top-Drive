//
// Created by Carte on 23/11/2025.
//

#include "../header/PlayerCar.h"
#include "../header/PhysicsWorld.h"
#include "../header/LoadSprites.h"
#include "../header/CarPhysics.h"
#include <cmath>

CarPhysics::CarPhysics(PhysicsWorld& physics, const CarSpec &spec, const b2Vec2 &startPosMeters) : m_physics(physics), m_car(spec) {

    //Create Box2D body from the chassis
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = startPosMeters;
    m_body = m_physics.world().CreateBody(&bodyDef);

    float fullWidth = 1.8f; // 1.8 meters
    float fullLength = 4.2; // 4.2 meters
    float scale = 2.7f;

    // Basic box shop from a default size to fit chassis
    float halfWidth = fullWidth * 0.5f / scale;
    float halfHeight = fullLength * 0.5f / scale;

    b2PolygonShape boxShape;
    boxShape.SetAsBox(halfWidth, halfHeight);

    // Calulate density as mass
    float area = fullLength * fullLength; // m^2
    float density = spec.chassis.massKg / area; // kg / m^2

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = density;
    fixtureDef.friction = 1.0f;
    m_body->CreateFixture(&fixtureDef);

    m_body->SetLinearDamping(0.3f);
    m_body->SetAngularDamping(1.1f);

}

b2Body* CarPhysics::getBody() { return m_body; }
Car& CarPhysics::getCar() { return m_car; }
const Car& CarPhysics::getCar() const { return m_car; }

void CarPhysics::update(const MovementIntent &intent, float dt) {
    if (!m_body) return;

    // Aprox wheel speed from velocity following forward direction
    const float wheelRadius = 0.3f;



    b2Vec2 vel = m_body->GetLinearVelocity();
    float angle = m_body->GetAngle();

    b2Vec2 fwd(-std::sin(angle), std::cos(angle)); // The car is facing up (Hopefully)

    float forwardSpeed = b2Dot(vel, fwd); // m/s from car moving forward
    float wheelOmega = 0.f;

    if (wheelRadius > 0.f) {
        wheelOmega = forwardSpeed / wheelRadius; // rad/s sadly
    }

    // Cancel some lateral sliding
    applyLateralFriction(dt);


    //Split throttle into acceleration and brake / reverse
    float throttle = intent.throttle;
    float accel = 0.f;
    float brake = 0.f;
    float reverse = 0.f;
    if (throttle > 0.f) {
        accel = throttle;
    } else if (throttle < 0.f) {
        if (forwardSpeed > 1.f) {
            brake = -throttle;
        } else {
            reverse = -throttle;
        }
    }

    float engineThrottle = accel + reverse;

    // Update drive and engine state
    m_car.updateDrivetrain(engineThrottle, brake, wheelOmega, dt);

    // Apply force and torque to car
    applyDrive(intent, forwardSpeed, wheelRadius, dt);
    applySteering(intent, forwardSpeed);
    applyBraking(intent, vel, forwardSpeed, dt);
}

void CarPhysics::applyDrive(const MovementIntent &intent, float forwardSpeed, float wheelRadius, float dt) {
    if (!m_body) return;

    float throttle = intent.throttle;
    float accel = (throttle > 0.f) ? throttle : 0.f;
    float reverse = 0.f;

    // Calculate drive torque at wheels
    if (throttle > 0.01f) {
        accel = throttle; // forward
    } else if (throttle < 0.f && std::fabs(forwardSpeed) < 1.0f) {
        reverse = -throttle;
    }

    float driveAmount = accel + reverse;
    if (driveAmount < 0.01f) {
        return;
    }

    float torqueLimiter = 0.3f;
    float totalWheelTorque = m_car.getWheelTorque() * driveAmount * torqueLimiter;

    // Turn torque into drive force going forward
    float driveForceM = 0.f;
    if (wheelRadius > 0.f) {
        driveForceM = totalWheelTorque / wheelRadius;
    }

    if (std::fabs(driveForceM) > 0.001f) {
        float angle = m_body->GetAngle();
        b2Vec2 fwd(-std::sin(angle), std::cos(angle));
        float dir = (accel > 0.f) ? 1.0f : -1.0f;
        b2Vec2 driveForce = (driveForceM * dir) * fwd;
        m_body->ApplyForceToCenter(driveForce, true);
    }
}

void CarPhysics::applySteering(const MovementIntent &intent, float forwardSpeed) {
    if (!m_body) return;

    const float baseTurnSpeed = 13.5f;
    const float minSteerSpeed = 0.5f;
    const float steerScaleSpeed = 10.f;

    float speedForward = std::fabs(forwardSpeed);

    if (speedForward < minSteerSpeed) {
        m_body->SetAngularVelocity(0.0f);
        return;
    }

    float speedFactor = std::min(speedForward / steerScaleSpeed,  1.f);
    float direction = (forwardSpeed >= 0.f) ? 1.f : -1.f;

    float desiredAngularVel = intent.steer * baseTurnSpeed * speedFactor * direction;
    m_body->SetAngularVelocity(desiredAngularVel);
}

void CarPhysics::applyBraking(const MovementIntent &intent, const b2Vec2 &vel, float forwardSpeed, float dt) {
    if (!m_body) return;

    float throttle = intent.throttle;
    float brake = 0.f;
    if (throttle < 0.f && forwardSpeed > 0.5f) {
        brake = -throttle;
    }

    if (brake <= 0.01f) return;

    float baseBrakeForce = m_car.getBaseBrakeForce();
    float brakeForce = baseBrakeForce * brake;

    b2Vec2 brakeDir = -vel;
    float speed = vel.Length();
    if (speed <= 0.001f) return;

    brakeDir *= (1.f / speed);

    float brakeImpulseMag = brakeForce * dt;
    b2Vec2 brakeImpulse = brakeImpulseMag * brakeDir;

    m_body->ApplyLinearImpulseToCenter(brakeImpulse, true);

}

void CarPhysics::applyLateralFriction(float dt) {
    if (!m_body) return;

    float angle = m_body->GetAngle();

    // Forward and right vector
    b2Vec2 fwd(-std::sin(angle), std::cos(angle));
    b2Vec2 right(fwd.y, -fwd.x);

    b2Vec2 vel = m_body->GetLinearVelocity();

    // Lateral Velocity
    float lateralSpeed = b2Dot(vel,right);
    b2Vec2 lateralVel = lateralSpeed * right;

    float mass = m_body->GetMass();

    // Impulse to cancel out sideways movements hopefully
    b2Vec2 impulse = -mass * lateralVel;

    //Clamp to so my car doesent stop instatly sliding at 60mph
    float maxsLateralImpulse = mass * 10.0f;
    float impLen = impulse.Length();
    if (impLen > maxsLateralImpulse) {
        impulse *= (maxsLateralImpulse / impLen);
    }

    m_body->ApplyLinearImpulseToCenter(impulse, true);

    // rolling resistance
    float forwardSpeed = b2Dot(vel, fwd);
    b2Vec2 forwardVel = forwardSpeed * fwd;

    float dragCoeffienct = 0.5f; // Drag coeffcient If too strong change me

    b2Vec2 dragForce = -dragCoeffienct * forwardVel;
    m_body->ApplyForceToCenter(dragForce, true);

}

void CarPhysics::drawDebug(sf::RenderWindow& window)
{
    // Get body position in pixels
    b2Vec2 posMeters = m_body->GetPosition();
    float angle = m_body->GetAngle();

    sf::RectangleShape debugShape;

    // Get fixture shape
    b2Fixture* fixture = m_body->GetFixtureList();
    b2PolygonShape* poly = static_cast<b2PolygonShape*>(fixture->GetShape());

    // Box2D gives half-width/half-height in meters
    float halfW = poly->m_vertices[1].x; // local vertex
    float halfH = poly->m_vertices[2].y;

    debugShape.setSize({
        m_physics.toPixels(halfW * 2.f),
        m_physics.toPixels(halfH * 2.f)
    });

    debugShape.setOrigin(debugShape.getSize() / 2.f);

    debugShape.setFillColor(sf::Color::Transparent);
    debugShape.setOutlineThickness(2.f);
    debugShape.setOutlineColor(sf::Color::Red);

    debugShape.setPosition(m_physics.toPixels(posMeters.x),
                           m_physics.toPixels(posMeters.y));
    debugShape.setRotation(angle * 180.f / b2_pi);

    window.draw(debugShape);
}





