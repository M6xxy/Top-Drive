#include <SFML/Graphics.hpp>
#include <../../../../header/Movement.h>
#include <box2d/box2d.h>
#include "header/CarComponents.h"
#include "header/Car.h"
#include "header/PlayerCar.h"
#include "header/LoadSprites.h"
#include "header/PhysicsWorld.h"
#include "header/Player.h"

static CarSpec makeTestCarSpec() {
    CarSpec spec;
    spec.name = "Test Car";

    // ENGINE
    spec.engine.name        = "2.0 NA";
    spec.engine.maxPowerKW  = 110.f;
    spec.engine.maxTorqueNM = 200.f;
    spec.engine.rpmLimit    = 7500.f;
    spec.engine.idleRpm     = 900.f;
    spec.engine.flywheelInertia     = 0.25f;

    // Very rough torque curve (rpm, Nm)
    spec.engine.torqueCurve = {
        {1000.f, 120.f},
        {3000.f, 180.f},
        {5000.f, 200.f},
        {7000.f, 180.f}
    };

    // BRAKES
    spec.brakes.name        = "Sport brakes";
    spec.brakes.frontForce  = 8000.f;
    spec.brakes.rearForce   = 5000.f;
    spec.brakes.bias        = 0.6f;
    spec.brakes.fadeCoefficient   = 0.1f;

    // CHASSIS
    spec.chassis.name            = "Lightweight";
    spec.chassis.massKg          = 950.f;
    spec.chassis.wheelBase      = 2.5f;
    spec.chassis.trackFront     = 1.5f;
    spec.chassis.trackRear      = 1.5f;
    spec.chassis.cogHeight      = 0.45f;
    spec.chassis.weightDistFront = 0.55f;

    // SUSPENSION (placeholder)
    spec.suspension.name            = "Sport";
    spec.suspension.springRateFront = 30000.f;
    spec.suspension.springRateRear  = 28000.f;
    spec.suspension.damperFront     = 3000.f;
    spec.suspension.damperRear      = 2800.f;
    spec.suspension.rideHeightFront = 0.12f;
    spec.suspension.rideHeightRear  = 0.13f;
    spec.suspension.camberFront     = -1.5f;
    spec.suspension.camberRear      = -1.0f;
    spec.suspension.toeFront        = 0.1f;
    spec.suspension.toeRear         = 0.0f;

    // TYRES
    spec.tyre.name        = "Street Tyres";
    spec.tyre.grip        = 1.0f;
    spec.tyre.wearRate    = 0.01f;
    spec.tyre.tempOptimal = 80.f;
    spec.tyre.tempRange   = 40.f;

    // TRANSMISSION
    spec.transmission.name            = "6-speed FWD";
    spec.transmission.numGears        = 6;
    spec.transmission.automatic       = false;
    spec.transmission.finalDriveRatio = 4.1f;
    spec.transmission.gearRatios      = {3.3f, 2.1f, 1.5f, 1.2f, 1.0f, 0.8f};
    spec.transmission.awdFrontTorqueSplit   = 0.5f;          // not used for FWD
    spec.transmission.driveType       = DriveType::FWD;

    return spec;
}

int main() {

  //DELTA CLOCK
  sf::Clock dt_clock;

  //Create Window
  sf::RenderWindow window(sf::VideoMode({800, 800}), "SFML works!");

  //Limit FPS
  window.setFramerateLimit(60);

  //Circle Object
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  // Create Physics World
  LoadSprites spriteLoader;
  PhysicsWorld physics({0.f, 0.f}, 30.f);
  Movement movement;


CarSpec debugCarSpec = makeTestCarSpec();

  PlayerCar playerCar(
    physics,
    spriteLoader,
    "../../assets/textures/placeholder-car.png",
    {400.f, 400.f},
    debugCarSpec
  );

  //GAME LOOP
  while (window.isOpen()) {
    // 1. Event handling
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // 2. Delta time
    float dt = dt_clock.restart().asSeconds();

    // 3. Movement Intent
    MovementIntent intent = movement.captureInput();

    // Physics
    playerCar.updatePhysics(intent, dt);
    physics.step(dt);
    playerCar.syncSpriteFromPhysics();

    // 4. Render
    window.clear();
    window.draw(shape);
    window.draw(playerCar.getSprite());
    window.display();
  }
}
