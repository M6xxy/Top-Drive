#include <SFML/Graphics.hpp>
#include <../../../../header/Movement.h>
#include <box2d/box2d.h>

#include "cpps/Game Conditions/CheckpointHandler.h"
#include "header/CarComponents.h"
#include "header/Car.h"
#include "header/PlayerCar.h"
#include "header/LoadSprites.h"
#include "cpps/Scenes/MenuScene.h"
#include "cpps/UI/rpmGauge.h"
#include "header/PhysicsWorld.h"
#include "header/CollisionCreator.h"
#include "header/MapEditor.h"
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

  //MENU STATE
  int menuState = 0;

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

  //Menu
  MenuScene mainMenu(window);

  // RPM Gauge
  rpmGauge RPMGauge;


CarSpec debugCarSpec = makeTestCarSpec();

  PlayerCar playerCar(
    physics,
    spriteLoader,
    "../../assets/textures/placeholder-car.png",
    {75.f, 100.f},
    debugCarSpec
  );

  //Load Map Editor
  MapEditor mapEditor;
  b2Vec2 gravity(0.0f, 0.0f);
  b2World world(gravity);

  //Create Map
  int track[12][12] = {
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,2,0,0,0},
    {0,1,3,0,0,0,4,1,1,1,0,0},
    {0,1,1,99,1,1,0,0,5,1,0,0},
    {0,0,0,0,0,1,0,0,0,1,0,0},
    {0,1,99,1,0,1,0,0,0,1,0,0},
    {0,1,5,1,2,1,0,0,0,1,2,0},
    {0,1,0,1,1,1,0,0,0,1,1,0},
    {0,1,0,0,0,0,0,0,0,4,1,0},
    {0,1,99,1,2,1,1,1,1,2,99,0},
    {0,0,4,1,1,1,5,5,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0}
  };

  Map testMap;
  // Set tiles in testMap
  for(int y = 0; y < 12; y++) {
    for(int x = 0; x < 12; x++) {
      testMap.setTile(track[y][x], x, y);
    }
  }

  //Create Collsion
  CollisionCreator collisionCreator;
  collisionCreator.createCollision(physics.world(),collisionCreator.tileCollisonVector,testMap);

  //Get Checkpoints
  CheckpointHandler checkpointHandler(testMap);

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

    //Get mouse properties
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // 3. Movement Intent
    MovementIntent intent = movement.captureInput();

    // Physics
    playerCar.updatePhysics(intent, dt);
    physics.step(dt);
    playerCar.syncSpriteFromPhysics();

    // Update RPM gauge
    RPMGauge.update(playerCar.getCar());

    // 4. Render

    //Menu
    if (mainMenu.state == 0) {
      mainMenu.update(mousePos,mousePressed);
      window.clear();
      mainMenu.draw(window);
    } else {
      //Map
      testMap.render(mapEditor.tileLibrary,window);
      //Collision display
      collisionCreator.render(window,collisionCreator.tileInstances);
      playerCar.m_carPhysics.drawDebug(window);
      //Player Sprite
      window.draw(playerCar.getSprite());
      //RPM Gauge
      RPMGauge.setVisible(true);
      RPMGauge.draw(window);
      //Check checkpoints
      checkpointHandler.checkIfInCheckpoints(playerCar);

    }


    //Display
    window.display();
  }
}
