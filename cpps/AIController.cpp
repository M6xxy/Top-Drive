//
// Created by Carte on 06/12/2025.
//

#include "../header/AIController.h"
#include  <algorithm>
#include  <cmath>

AIController::AIController(PhysicsWorld &physics, const std::vector<sf::Vector2f> &waypointsPixels, float targetSpeed) : m_physics(physics), m_targetSpeed(targetSpeed) {

    m_waypoints.reserve(waypointsPixels.size());
    for (auto& p : waypointsPixels) {
        m_waypoints.push_back(b2Vec2(m_physics.toMeters(p.x), m_physics.toMeters(p.y)));
    }

    if (m_waypoints.empty()) {
        m_waypoints.push_back(b2Vec2(0.f, 0.f));
    }
}

b2Vec2 AIController::getCurrentWaypoint() const {
    return m_waypoints[m_currentIndex % m_waypoints.size()];
}

void AIController::advanceWaypointIfClose(const b2Vec2& carPos) {
    b2Vec2 currentWaypoint = getCurrentWaypoint(); // Current AI checkpoint it is driving too
    b2Vec2 diffrence = currentWaypoint - carPos; // Diffrence  between cars position and the checkpoints position
    float distance = diffrence.LengthSquared();

    const float radius = 2.f; // Meters
    if (distance < radius * radius) {
        m_currentIndex = (m_currentIndex + 1) % m_waypoints.size();
    }
}

MovementIntent AIController::update(const CarPhysics& carPhys, float dt) {
    MovementIntent intent; // Setup intent to allow the ai to control the car

    const b2Body* body = carPhys.getBody();
    if (!body || m_waypoints.empty())
        return intent;

    b2Vec2 pos = body->GetPosition(); // Gets the cars current position
    float angle = body->GetAngle(); // Gets the cars current angle of rotation

    b2Vec2 fwd(-std::sin(angle), std::cos(angle));
    b2Vec2 vel = body->GetLinearVelocity(); // Cars moving velocity

    advanceWaypointIfClose(pos); // Advanced to next checkpoint based on ai's current position

    b2Vec2 currentWaypoint = getCurrentWaypoint(); // What check is the ai current at?

    // Steering towards waypoint
    b2Vec2 toWP = currentWaypoint - pos;
    float distanceTWP = toWP.Length(); // Distance to waypoint
    if (distanceTWP > 0.0001f) {
        toWP *= (1.f / distanceTWP);
    } else {
        toWP.SetZero();
    }

    float dot = b2Dot(fwd, toWP);
    dot = std::clamp(dot, -1.0f, 1.0f);
    float cross = fwd.x * toWP.y - fwd.y * toWP.x; // Left / right

    float angleDiff = std::acos(dot);
    if (cross < 0.f) angleDiff = -angleDiff;

    const float maxSteer = 1.f; // Max steering angle for the ai car
    const float steerGain = 2.5f; // Adjust this to change how it steers

    intent.steer = std::clamp(angleDiff * steerGain, -maxSteer, maxSteer);

    // Speed controll of the car
    float speed = vel.Length(); // m/s
    float speedError = m_targetSpeed - speed;

    const float accelGain = 0.05f; // How fast the car accelerates (USE THIS AND THE OTHER VARIABLES TO ADJUST DIFFICULTY)
    float throttleCmd = speedError * accelGain;

    if (throttleCmd > 0.f) {
        // Accelerate car
        intent.throttle = std::clamp(throttleCmd, 0.f, 1.f);
    } else {
        // Slow the car down
        float brake = std::clamp(-throttleCmd, 0.f, 1.f);
        intent.throttle = -brake;
    }

    intent.handbrake = false;

    return intent;
}

