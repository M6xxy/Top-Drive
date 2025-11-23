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

// Drive Type
enum class DriveType {
    FWD,
    RWD,
    AWD
};

// Transmission

struct TransmissionSpec {
    std::string name;

    int numGears; // How many gears the transmission has
    bool automatic; // Is the gearbox automatic?;
    float finalDriveRatio; // Higher = Higher top speed but slower acceleration, Lower = Faster acceleration but slower top speed

    std::vector<float> gearRatios;

    // AWD DRIVE ONLY TORQUE SPLIT
    float awdFrontTorqueSplit  = 0.5f;

    DriveType driveType;
};

// Chassis

struct ChassisSpec {
    std::string name;

    float massKg; // Overall chassis weight
    float wheelBase; // Distance between front and rear axles, Shorter = more agile but less stable at higher speeds
    float trackFront; // Distance between front left and right tyres
    float trackRear; // Distance between rear left and right tyres
    float cogHeight; // Centre of gravity height in meters above ground, Lower = more stable but less roll
    float weightDistFront; // Weight distribution between front and rear 0.0 = all rear, 1 = full front

};

// Suspension
struct SuspensionSpec {
    std::string name;

    float springRateFront; // How quickly the spring compresses
    float springRateRear; // How quickly the spring compresses
    float damperFront; // How hard the springs resists compression
    float damperRear; // How hard the springs resists compression
    float rideHeightFront; // Height from the road
    float rideHeightRear; // Height from the road
    float camberFront; // Wheels camber 0-1
    float camberRear; // Wheels camber 0-1
    float toeFront; // Wheels toe 0-1
    float toeRear; // Wheels toe 0-1
};

// Tyres
struct TyreSpec {
    std::string name;

    float grip; // Grip coefficient
    float wearRate; // How quickly the tyres wear down (!MORE WEAR = LESS GRIP THAN NEW TYRE!)
    float tempOptimal; // Ideal tyre temp
    float tempRange; // Optimal tyre temp range for grip
};

// Full car config
struct CarSpec {
    std::string name;

    EngineSpec engine;
    TransmissionSpec  transmission;
    BrakeSpec brakes;
    ChassisSpec chassis;
    SuspensionSpec suspension;
    TyreSpec tyre;
};