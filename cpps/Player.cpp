//
// Created by Carte on 20/11/2025.
//

#include "../header/Player.h"
#include "../header/PhysicsWorld.h"
#include "../header/LoadSprites.h"
#include "../header/Movement.h"

Player::Player(PhysicsWorld& physics, LoadSprites& loader, const std::string& texturePath,
    const sf::Vector2f& startPosPixels, float speedMetersPerSec) : m_physics(physics),
    m_body(nullptr), m_speed(speedMetersPerSec) {

    // Load sprite and texture via loader
    loader.Load(m_sprite, m_texture, texturePath);
    m_sprite.setPosition(startPosPixels);


    //Centre
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    //Set Scale
    m_sprite.setScale(0.2f,0.2f);


    // Create Box2D Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_physics.toMeters(startPosPixels.x), m_physics.toMeters(startPosPixels.y));
    m_body = m_physics.world().CreateBody(&bodyDef);

    // Change shape based on sprite
    b2PolygonShape boxShape;
    float hitboxScale = 0.5f; // 50% of sprite

    boxShape.SetAsBox(
        m_physics.toMeters((bounds.width  * m_sprite.getScale().x * hitboxScale) / 2.f),
        m_physics.toMeters((bounds.height * m_sprite.getScale().y * hitboxScale) / 2.f)
    );

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    m_body->CreateFixture(&fixtureDef);

    m_body->SetLinearDamping(2.0f);
    m_body->SetAngularDamping(3.0f);
}

void Player::updatePhysics(const MovementIntent &intent) const {
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

void Player::drawDebug(sf::RenderWindow& window)
{
    // Get body position in pixels
    b2Vec2 posMeters = m_body->GetPosition();
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

