//
// Created by Carte on 23/11/2025.
//

#include "../header/PlayerCar.h"
#include "../header/PhysicsWorld.h"
#include "../header/LoadSprites.h"
#include "../header/Movement.h"
#include <cmath>

PlayerCar::PlayerCar(PhysicsWorld &physics, LoadSprites &loader, const std::string &texturePath,
    const sf::Vector2f& startPosPixels, const CarSpec &spec) : m_physics(physics), m_carPhysics(physics, spec, b2Vec2(physics.toMeters(startPosPixels.x), physics.toMeters(startPosPixels.y))){
    loader.Load(m_sprite, m_texture, texturePath); // Pass sprite to loader to texture
    m_sprite.setPosition(startPosPixels); // Set initial position of players car

    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    m_sprite.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);

}

void PlayerCar::updatePhysics(const MovementIntent &intent, float dt) {
    m_carPhysics.update(intent, dt);
}

void PlayerCar::syncSpriteFromPhysics() {
    b2Body* body = m_carPhysics.getBody();
    if (!body) return;

    b2Vec2 pos = body->GetPosition();
    float angle = body->GetAngle();

    m_sprite.setPosition(
        m_physics.toPixels(pos.x),
        m_physics.toPixels(pos.y)
    );

    m_sprite.setRotation(angle * 180.f / b2_pi);

}

void PlayerCar::drawDebug(sf::RenderWindow& window)
{
    // Get body position in pixels
    b2Vec2 posMeters = m_carPhysics->GetPosition();
    float angle = m_body->GetAngle();

    sf::RectangleShape debugShape;

    // Get fixture shape
    b2Fixture* fixture = m_body->GetFixtureList();
    b2PolygonShape* poly = static_cast<b2PolygonShape*>(fixture->GetShape());

    // Box2D gives half-width/half-height in meters
    float halfW = poly->m_vertices[1].x; // local vertex
    float halfH = poly->m_vertices[2].y;

    debugShape.setSize({
        m_physics.toPixels(halfW * 2.f),
        m_physics.toPixels(halfH * 2.f)
    });

    debugShape.setOrigin(debugShape.getSize() / 2.f);

    debugShape.setFillColor(sf::Color::Transparent);
    debugShape.setOutlineThickness(2.f);
    debugShape.setOutlineColor(sf::Color::Red);

    debugShape.setPosition(m_physics.toPixels(posMeters.x),
                           m_physics.toPixels(posMeters.y));
    debugShape.setRotation(angle * 180.f / b2_pi);

    window.draw(debugShape);
}

sf::Sprite& PlayerCar::getSprite() { return m_sprite; }
Car& PlayerCar::getCar() { return m_carPhysics.getCar(); }
const Car& PlayerCar::getCar() const { return m_carPhysics.getCar(); }


