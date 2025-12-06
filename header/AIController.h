//
// Created by Carte on 06/12/2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Movement.h"
#include "CarPhysics.h"
#include "PhysicsWorld.h"

class AIController {

public:
    AIController(PhysicsWorld& physics,
        const std::vector<sf::Vector2f>& waypointsPixels,
        float targetSpeed = 18.0f); // ADD ME TO SETTINGS TO CHANGE DIFFICULTY - CM

    //Get AI input every frame
    MovementIntent update(const CarPhysics& carPhys, float dt);

private:
    PhysicsWorld& m_physics;
    std::vector<b2Vec2> m_waypoints; // Waypoints in meteres from each other
    std::size_t m_currentIndex = 0;
    float m_targetSpeed; // m/s

    b2Vec2 getCurrentWaypoint() const;  // Get current waypoint car is at
    void advanceWaypointIfClose(const b2Vec2& carPos); // Continue to next waypoint if close to current waypoint
};