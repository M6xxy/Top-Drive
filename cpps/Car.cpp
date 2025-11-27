//
// Created by Carte on 23/11/2025.
//

#include "../header/Car.h"
#include <algorithm>
#include  <cmath>

Car::Car(const CarSpec& spec) : m_spec(spec) {
    m_state.rpm = spec.engine.idleRpm;
    m_state.gear = 1;
}

const CarSpec& Car::getSpec() const { return m_spec; }
const CarState& Car::getState() const { return m_state; }


void Car::updateDrivetrain(float throttle, float brake, float wheelAngularSpeed, float dt) {
    //Clamp Inputs
    throttle = std::clamp(throttle, 0.0f, 1.0f);
    brake = std::clamp(brake, 0.0f, 1.0f);

    const auto& eng = m_spec.engine;
    const auto& trans = m_spec.transmission;

    float rpm = m_state.rpm;

    // Calculate engine rpm from wheel speed and gearing
    if (m_state.gear > 0 && m_state.gear <= trans.numGears) {
        float gearRatio = trans.gearRatios[m_state.gear - 1];
        float totalRatio = gearRatio * trans.finalDriveRatio;

        // Change wheel speed to engine rpm and convert
        float engineRadPerSec = wheelAngularSpeed * totalRatio;
        float targetRpm = engineRadPerSec * (60.f / (2.f * 3.14));

        // If wheels are not turning fast let throttle pull rpm higher up to accomodate
        if (std::fabs(wheelAngularSpeed) < 0.5f) {
            float freeRevTarget = eng.idleRpm + throttle * (eng.rpmLimit - eng.idleRpm);
            // User whatever rpm  is higher wheel based rpm or free moving
            targetRpm = std::max(targetRpm, freeRevTarget);
        }

        // Simulate engine inertia
        float rpmDiff = targetRpm - rpm;
        float maxDelta = eng.flywheelInertia > 0.f ? (dt * 8000.f / eng.flywheelInertia) : 999999.f;
        rpmDiff = std::clamp(rpmDiff, -maxDelta, maxDelta);
        rpm += rpmDiff;
    } else {
        // If cars in neutral rely solely on throttle
        float targetRpm = eng.idleRpm + throttle * (eng.rpmLimit - eng.idleRpm);
        float rpmDiff = targetRpm - rpm;
        float maxDelta = dt * 4000.f;
        rpmDiff = std::clamp(rpmDiff, -maxDelta, maxDelta);
        rpm += rpmDiff;
    }

    //Convert rpm to a reasonable range
    rpm = std::clamp(rpm, eng.idleRpm * 0.5f, eng.rpmLimit * 1.05f);

    m_state.rpm = rpm;
}

float Car::getWheelTorque() const {
    const auto& eng = m_spec.engine;
    const auto& trans = m_spec.transmission;

    if (m_state.gear <= 0 || m_state.gear > trans.numGears)
        return 0.0f;

    float engineTorque = eng.getTorqueAtRpm(m_state.rpm);

    float gearRatio = trans.gearRatios[m_state.gear - 1];
    float totalRatio = gearRatio * trans.finalDriveRatio;

    // Take into account real world losses such as bad roads, worn bushes etc
    float efficiency = 0.9f;

    return engineTorque * totalRatio * efficiency;
}

float Car::getBaseBrakeForce() const {
    const auto& brakes = m_spec.brakes;

    // Combine front and rear to estimate max braking force
    return brakes.frontForce + brakes.rearForce;
}

void Car::getAxleTorque(float &frontTorqueOut, float &rearTorqueOut) const {
    float totalWheelTorque = getWheelTorque();

    const auto& trans = m_spec.transmission;
    switch (trans.driveType) {
        case DriveType::FWD: {
            frontTorqueOut = totalWheelTorque;
            rearTorqueOut = 0.0f;
        } break;
        case DriveType::RWD: {
            frontTorqueOut = 0.0f;
            rearTorqueOut = totalWheelTorque;
        } break;
        case DriveType::AWD: {
            float frontFrac = trans.awdFrontTorqueSplit;
            frontFrac = std::clamp(frontFrac, 0.0f, 1.0f);
            frontTorqueOut = totalWheelTorque * frontFrac;;
            rearTorqueOut = totalWheelTorque * (1.f - frontFrac);
        } break;
    }
}







