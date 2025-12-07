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
    spec.chassis.wheelBase      = 2.5f;
    spec.chassis.trackFront     = 1.5f;
    spec.chassis.trackRear      = 1.5f;
    spec.chassis.cogHeight      = 0.45f;
    spec.chassis.weightDistFront = 0.55f;

    // SUSPENSION (placeholder)
    spec.suspension.name            = "Sport";
    spec.suspension.springRateFront = 30000.f;
    spec.suspension.springRateRear  = 28000.f;
    spec.suspension.damperFront     = 3000.f;
    spec.suspension.damperRear      = 2800.f;
    spec.suspension.rideHeightFront = 0.12f;
    spec.suspension.rideHeightRear  = 0.13f;
    spec.suspension.camberFront     = -1.5f;
    spec.suspension.camberRear      = -1.0f;
    spec.suspension.toeFront        = 0.1f;
    spec.suspension.toeRear         = 0.0f;

    // TYRES
    spec.tyre.name        = "Street Tyres";
    spec.tyre.grip        = 1.0f;
    spec.tyre.wearRate    = 0.01f;
    spec.tyre.tempOptimal = 80.f;
    spec.tyre.tempRange   = 40.f;

    // TRANSMISSION
    spec.transmission.name            = "6-speed FWD";
    spec.transmission.numGears        = 6;
    spec.transmission.automatic       = false;
    spec.transmission.finalDriveRatio = 4.1f;
    spec.transmission.gearRatios      = {3.3f, 2.1f, 1.5f, 1.2f, 1.0f, 0.8f};
    spec.transmission.awdFrontTorqueSplit   = 0.5f;          // not used for FWD
    spec.transmission.driveType       = DriveType::FWD;

    return spec;
}
