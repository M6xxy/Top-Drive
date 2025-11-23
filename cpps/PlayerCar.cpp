//
// Created by Carte on 23/11/2025.
//

#include "../header/PlayerCar.h"
#include "../header/PhysicsWorld.h"
#include "../header/LoadSprites.h"
#include "../header/Movement.h"
#include <cmath>

PlayerCar::PlayerCar(PhysicsWorld &physics, LoadSprites &loader, const std::string &texturePath, const sf::Vector2f& startPosPixels, const CarSpec &spec) : m_physics(physics), m_car(spec){
    loader.Load(m_sprite, m_texture, texturePath); // Pass sprite to loader to texture
    m_sprite.setPosition(startPosPixels); // Set initial position of players car

    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    m_sprite.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);

    // Create box2d Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_physics.toMeters(startPosPixels.x), m_physics.toMeters(startPosPixels.y));

    m_body = m_physics.world().CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(m_physics.toMeters(bounds.width * 0.5f), m_physics.toMeters(bounds.height * 0.5f));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetLinearDamping(2.0f);
    m_body->SetAngularDamping(3.0f);
}

void PlayerCar::updatePhysics(const MovementIntent &intent, float dt) {
    if (!m_body) return;

    // Interpect movement intent as car controls
    float throttle = intent.throttle;
    float steer = intent.steer;
    bool handbrake = intent.handbrake;

    float accel = 0.f;
    float brake = 0.f;
    if (throttle > 0.f) {
        accel = throttle; // Go Forward
    } else if (throttle < 0.f) {
        brake = -throttle;
    }

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

    // Update drive and engine state
    m_car.updateDrivetrain(throttle, brake, wheelOmega, dt);

    // Calculate drive torque at wheels
    float totalWheelTorque = 0.f;
    if (accel > 0.01f) {
        totalWheelTorque = m_car.getWheelTorque() * throttle;
    }

    // Turn torque into drive force going forward
    float driveForceM = 0.f;
    if (wheelRadius > 0.f) {
        driveForceM = totalWheelTorque / wheelRadius;
    }

    if (std::fabs(driveForceM) > 0.001f) {
        b2Vec2 driveForce = driveForceM * fwd;
        m_body->ApplyForceToCenter(driveForce, true);
    }


    // set angular velocity based on users steering input
    const float turnSpeed = 2.5f; // rad/s at full steer
    float desiredAngularVel = steer * turnSpeed;
    m_body->SetAngularVelocity(desiredAngularVel);

    // Debug Braking
    if (brake > 0.01f) {
        float baseBrakeForce = m_car.getBaseBrakeForce();
        float brakeForce = baseBrakeForce * brake;

        b2Vec2 brakeDir = -vel;
        float speed = vel.Length();
        if (speed > 0.001f) {
            brakeDir *= (1.0f / speed);

            float brakeImpulseMag = brakeForce * dt;
            b2Vec2 brakeImpulse = brakeImpulseMag * brakeDir;

            m_body->ApplyLinearImpulseToCenter(brakeImpulse, true);
        }
    }
}

void PlayerCar::syncSpriteFromPhysics() {
    if (!m_body) return;

    b2Vec2 pos = m_body->GetPosition();
    float angle = m_body->GetAngle();

    m_sprite.setPosition(m_physics.toPixels(pos.x), m_physics.toPixels(pos.y));
    m_sprite.setRotation(angle * 180.f / b2_pi);
}

sf::Sprite& PlayerCar::getSprite() { return m_sprite; }
b2Body* PlayerCar::getBody() { return m_body; }
Car& PlayerCar::getCar() { return m_car; }
const Car& PlayerCar::getCar() const { return m_car; }


