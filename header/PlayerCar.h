//
// Created by Carte on 23/11/2025.
//

#pragma once

#include <box2d/box2d.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "CarPhysics.h"
#include "Movement.h"

class PhysicsWorld;
class LoadSprites;
struct MovementIntent;

class PlayerCar {
public:
    PlayerCar(PhysicsWorld& physics, LoadSprites& loader, const std::string& texturePath, const sf::Vector2f& startPosPixels, const CarSpec& spec);

    // Update car and box2d every frame
    void updatePhysics(const MovementIntent& intent, float dt);

    // Sync sprite from box2d
    void syncSpriteFromPhysics();

    // Helpers
    sf::Sprite& getSprite();
    Car& getCar();
    const Car& getCar() const;

private:
    PhysicsWorld& m_physics;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    CarPhysics m_carPhysics;
};