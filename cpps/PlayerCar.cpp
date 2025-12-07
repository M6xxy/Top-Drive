//
// Created by Carte on 23/11/2025.
//

#include "../header/PlayerCar.h"
#include "../header/PhysicsWorld.h"
#include "../header/LoadSprites.h"
#include "../header/Movement.h"
#include <cmath>
#include <iostream>

PlayerCar::PlayerCar(PhysicsWorld &physics, LoadSprites &loader, const std::string &texturePath,
                     const sf::Vector2f& startPosPixels,
                     const CarSpec &spec) : m_physics(physics),
                    m_carPhysics(physics, spec, b2Vec2(physics.toMeters(startPosPixels.x), physics.toMeters(startPosPixels.y))),
                    startingPos(physics.toMeters(startPosPixels.x), physics.toMeters(startPosPixels.y))
{
    loader.Load(m_sprite, m_texture, texturePath); // Pass sprite to loader to texture
    m_sprite.setPosition(startPosPixels); // Set initial position of players car

    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    m_sprite.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f); // make sure the sprite is position ontop of the physics bounds correctly
    m_sprite.setScale(0.15f,0.15f); // Set the cars size so the physics is correct



}

void PlayerCar::updatePhysics(const MovementIntent &intent, float dt) {
    m_carPhysics.update(intent, dt);// Update physics based on users intent such as brake etc
}

void PlayerCar::syncSpriteFromPhysics() {
    b2Body* body = m_carPhysics.getBody(); // Get the car
    if (!body) return; // If car doesent exist dont continue

    b2Vec2 pos = body->GetPosition(); // Get the cars position
    float angle = body->GetAngle(); // Get the cars angle

    m_sprite.setPosition( // Set the cars position after converting
        m_physics.toPixels(pos.x),
        m_physics.toPixels(pos.y)
    );

    m_sprite.setRotation(angle * 180.f / b2_pi); // Rotation the car so its facing the right way

}

sf::Sprite& PlayerCar::getSprite() { return m_sprite; }
Car& PlayerCar::getCar() { return m_carPhysics.getCar(); }
const Car& PlayerCar::getCar() const { return m_carPhysics.getCar(); }
CarPhysics& PlayerCar::getPhysics() { return m_carPhysics; }
const CarPhysics& PlayerCar::getPhysics() const { return m_carPhysics; }

void PlayerCar::reset() {
    m_carPhysics.getBody()->SetTransform(startingPos,1.55);
}



