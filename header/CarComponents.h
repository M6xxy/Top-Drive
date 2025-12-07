//
// Created by Carte on 23/11/2025.
//

#pragma once

#include <string>
#include <vector>

// Engine

struct EngineSpec {
    std::string name;

    float maxPowerKW; // Peak Engine Power in Kilowatts
    float maxTorqueNM; // Peak engine torque in Neutonmeters
    float rpmLimit; // Hard cut for RPM Limit
    float idleRpm; // Idle RPM
    float flywheelInertia; // How fast the rev changes (Lower = faster)

    // Torque curve based on rpm and torque
    std::vector<std::pair<float,float>> torqueCurve;

    float getTorqueAtRpm(float rpm) const;
};

// Brakes

struct BrakeSpec {
    std::string name;

    float frontForce; // Standard brake force
    float rearForce; // Standard rear brake force
    float bias; // Brake bias 0.5 = 50% front
    float fadeCoefficient; // How quickly brake fades with temp
};


// Transmission

struct TransmissionSpec {
    std::string name;

    int numGears; // How many gears the transmission has
    float finalDriveRatio; // Higher = Higher top speed but slower acceleration, Lower = Faster acceleration but slower top speed

    std::vector<float> gearRatios;

};

// Chassis

struct ChassisSpec {
    std::string name;

    float massKg; // Overall chassis weight

};


// Full car config
struct CarSpec {
    std::string name;

    EngineSpec engine;
    TransmissionSpec  transmission;
    BrakeSpec brakes;
    ChassisSpec chassis;
};