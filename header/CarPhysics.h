//
// Created by Carte on 23/11/2025.
//

#pragma once

#include <box2d/box2d.h>
#include "Car.h"
#include "Movement.h"

class PhysicsWorld;
class LoadSprites;
struct MovementIntent;

class CarPhysics {

public:
    CarPhysics(PhysicsWorld& physics, const CarSpec& spec, const b2Vec2& startPosMeters);

    // Update physics for car
    void update(const MovementIntent& intent, float dt);

    b2Body* getBody();
    const Car& getCar() const;
    Car& getCar();

private:
    PhysicsWorld& m_physics;
    Car m_car;
    b2Body* m_body = nullptr;

    //Helpers
    void applyDrive(const MovementIntent& intent, float forwardSpeed, float wheelRadius, float dt);

    void applySteering(const MovementIntent& intent, float forwardSpeed);

    void applyBraking(const MovementIntent& intent, const b2Vec2& vel, float dt);

};