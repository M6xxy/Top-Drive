//
// Created by Carte on 20/11/2025.
//

#include "../header/Player.h"
#include "../header/PhysicsWorld.h"
#include "../header/LoadSprites.h"
#include "../header/Movement.h"

Player::Player(PhysicsWorld& physics, LoadSprites& loader, const std::string& texturePath, const sf::Vector2f& startPosPixels, float speedMetersPerSec) : m_physics(physics), m_body(nullptr), m_speed(speedMetersPerSec) {
    // Load sprite and texture via loader
    loader.Load(m_sprite, m_texture, texturePath);
    m_sprite.setPosition(startPosPixels);

    //Centre
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    // Create Box2D Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_physics.toMeters(startPosPixels.x), m_physics.toMeters(startPosPixels.y));
    m_body = m_physics.world().CreateBody(&bodyDef);

    // Change shape based on sprite
    b2PolygonShape boxShape;
    boxShape.SetAsBox(m_physics.toMeters(bounds.width * 0.5f), m_physics.toMeters(bounds.height * 0.5f));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    m_body->CreateFixture(&fixtureDef);
}

void Player::updatePhysics(const MovementIntent &intent) {
    m_physics.applyMovementIntent(m_body, intent, m_speed);
}

void Player::syncSpriteFromPhysics() {
    if (!m_body) return;

    b2Vec2 pos = m_body->GetPosition();
    float angle = m_body->GetAngle();

    m_sprite.setPosition(m_physics.toPixels(pos.x), m_physics.toPixels(pos.y));
    m_sprite.setRotation(angle * 180.f / b2_pi);
}

sf::Sprite& Player::getSprite() {
    return m_sprite;
}

b2Body* Player::getBody() {
    return m_body;
}

