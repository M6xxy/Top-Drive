//
// Created by Carte on 23/11/2025.
//
#pragma once

#include "CarComponents.h"

// Debug Car Instance
struct CarState {
    float rpm = 1000.f; // Engines RPM
    float gear = 1; // 1 = First gear, 0 = neutral, -1 = reverse
    float clutch = 1.f; // 1 = fully engaged, 0 = disengaged
    float engineTemp = 90.f;
    float brakeTempF = 40.f; // Front Brake Temp
    float brakeTempR = 40.f; // Rear Brake Temp
    float tyreWear = 0.f;
};

class Car {
public:
    explicit Car(const CarSpec& spec);

    const CarSpec& getSpec() const;
    const CarState& getState() const;
    CarState getState();

    // Update RPM based on throttle input
    void updateDrivetrain(float throttle, float brake, float wheelAngularSpeed, float dt);

    // Total torque delivered to the driven wheels
    float getWheelTorque() const;

    // Total braking force available
    float getBaseBrakeForce() const;

    // Torque bias from front vs rar on drive type
    void getAxleTorque(float& frontTorqueOut, float& rearTorqueOut) const;

private:
    CarSpec m_spec;
    CarState m_state;
};

