//
// Created by M6XXY on 07/12/2025.
//

#include "CarSpecController.h"
#include "CarComponents.h"

CarSpec CarSpecController::makeTestCarSpec() {
    CarSpec spec;
    spec.name = "Test Car";

    // ENGINE
    spec.engine.name        = "2.0 NA";
    spec.engine.maxPowerKW  = 110.f;
    spec.engine.maxTorqueNM = 200.f;
    spec.engine.rpmLimit    = 7500.f;
    spec.engine.idleRpm     = 900.f;
    spec.engine.flywheelInertia     = 0.25f;

    // Very rough torque curve (rpm, Nm)
    spec.engine.torqueCurve = {
        {1000.f, 120.f},
        {3000.f, 180.f},
        {5000.f, 200.f},
        {7000.f, 180.f}
    };

    // BRAKES
    spec.brakes.name        = "Sport brakes";
    spec.brakes.frontForce  = 8000.f;
    spec.brakes.rearForce   = 5000.f;
    spec.brakes.bias        = 0.6f;
    spec.brakes.fadeCoefficient   = 0.1f;

    // CHASSIS
    spec.chassis.name            = "Lightweight";
    spec.chassis.massKg          = 950.f;

    // TRANSMISSION
    spec.transmission.name            = "6-speed FWD";
    spec.transmission.numGears        = 6;
    spec.transmission.finalDriveRatio = 4.1f;
    spec.transmission.gearRatios      = {3.3f, 2.1f, 1.5f, 1.2f, 1.0f, 0.8f};

    return spec;
}
