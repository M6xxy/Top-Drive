//
// Created by Carte on 20/11/2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <string>

#include "Movement.h"
#include "PhysicsWorld.h"

class LoadSprites;
class PhysicsWorld;

class Player {
public:
    Player (PhysicsWorld& physics, LoadSprites& loader, const std::string& texturePath, const sf::Vector2f& startPosPixels, float speedMetersPerSec);

    // Update physics intent to player
    void updatePhysics(const MovementIntent& intent) const;

    // Sync sprite to physics body
    void syncSpriteFromPhysics();

    //Draw
    sf::Sprite& getSprite();

    //Expose Body for customization
    b2Body* getBody();

    void drawDebug(sf::RenderWindow &window);

private:
    PhysicsWorld& m_physics;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    b2Body* m_body;
    float m_speed;

};
