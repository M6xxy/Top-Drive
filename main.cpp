#include <SFML/Graphics.hpp>
#include <../../../../header/Movement.h>
#include <box2d/box2d.h>

#include "cpps/Game Conditions/CheckpointHandler.h"
#include "cpps/Game Conditions/GameState.h"
#include "header/CarComponents.h"
#include "header/Car.h"
#include "header/PlayerCar.h"
#include "header/AIController.h"
#include "header/LoadSprites.h"
#include "cpps/Scenes/MenuScene.h"
#include "cpps/Scenes/SettingsScene.h"
#include "cpps/UI/rpmGauge.h"
#include "header/PhysicsWorld.h"
#include "header/CollisionCreator.h"
#include "header/MapEditor.h"
#include "header/Player.h"

GameState currentState = GameState::MAIN_MENU;


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
  Movement movement("../../keybinds.txt");

  //Menu
  enum class GameState {
    MAIN_MENU,
    GAME,
    SETTINGS
};

  MenuScene mainMenu(window);
  SettingsScene settingsMenu(window,movement);

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

  constexpr float TILE_SIZE = 64.f;

  auto tileCenter = [TILE_SIZE](int tileX, int tileY) {
    return sf::Vector2f(tileX * TILE_SIZE + TILE_SIZE * 0.5f, tileY * TILE_SIZE + TILE_SIZE * 0.5f);
  };

  std::vector<sf::Vector2f> aiPath = {
    // Top straight, heading right
    tileCenter(1, 1),
    tileCenter(5, 1),
    tileCenter(7, 1),

    // Top-right down to mid-right
    tileCenter(8, 2),
    tileCenter(9, 3),
    tileCenter(9, 5),
    tileCenter(9, 7),
    tileCenter(10, 8),

    // Bottom-right and bottom straight
    tileCenter(10, 9),
    tileCenter(10, 10),
    tileCenter(7, 10),
    tileCenter(3, 10),

    // Bottom-left to mid-left
    tileCenter(1, 9),
    tileCenter(1, 6),
    tileCenter(1, 2),

    // Close the loop back near start
    tileCenter(1, 1),
  };

  PlayerCar aiCar(
     physics,
     spriteLoader,
     "../../assets/textures/placeholder-car.png",
     tileCenter(1, 1),
     debugCarSpec
   );

  AIController ai_controller(physics, aiPath, 8.f); // Target speed m/s

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

      //Pause Menu
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F1) {
          mainMenu.state = 1;
          currentState = ::GameState::MAIN_MENU;
        }
      }

      //Binding logic
        if (event.type == sf::Event::KeyPressed) {
          if (settingsMenu.waitingForForwardKey) {
            movement.p1Forward = event.key.code;
            //Save to file
            settingsMenu.saveKeybinds(movement);
            //Update Text
            settingsMenu.menu.setText(1,"Forward : " + movement.keyToString(event.key.code));
            //end
            settingsMenu.waitingForForwardKey = false;
          }

          //Left
          if (settingsMenu.waitingForLeftKey) {
            movement.p1Left = event.key.code;
            //Save to file
            settingsMenu.saveKeybinds(movement);
            //Update Text
            settingsMenu.menu.setText(3,"Left : " + movement.keyToString(event.key.code));
            //end
            settingsMenu.waitingForLeftKey = false;
          }

          //Right
          if (settingsMenu.waitingForRightKey) {
            movement.p1Right = event.key.code;
            //Save to file
            settingsMenu.saveKeybinds(movement);
            //Update Text
            settingsMenu.menu.setText(4,"Right : " + movement.keyToString(event.key.code));
            //end
            settingsMenu.waitingForRightKey = false;
          }

          //Back
          if (settingsMenu.waitingForBackKey) {
            movement.p1Back = event.key.code;
            //Save to file
            settingsMenu.saveKeybinds(movement);
            //Update Text
            settingsMenu.menu.setText(2,"Back : " + movement.keyToString(event.key.code));
            //end
            settingsMenu.waitingForBackKey = false;
          }
        }
    }

    // 2. Delta time
    float dt = dt_clock.restart().asSeconds();

    //Get mouse properties
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // 3. Movement Intent
    MovementIntent intent = movement.captureInput();
    MovementIntent aiIntent = ai_controller.update(aiCar.getPhysics(), dt);

    // Physics
    playerCar.updatePhysics(intent, dt);

    // AI
    aiCar.updatePhysics(aiIntent, dt);

    physics.step(dt);

    playerCar.syncSpriteFromPhysics();
    aiCar.syncSpriteFromPhysics();

    // Update RPM gauge
    RPMGauge.update(playerCar.getCar());

    // 4. Render
    window.clear();

    switch (currentState) {
      case ::GameState::MAIN_MENU:
        mainMenu.update(mousePos,mousePressed);
        mainMenu.draw(window);
        if (mainMenu.state == 2) {
          std::cout << "SETTING STATE TO GAME";
          currentState = ::GameState::GAME;
        }

        if (mainMenu.stateSettings == 1) {
          settingsMenu.stateSettings = 1;
          std::cout << "SETTING STATE TO SETTINGS";
          currentState = ::GameState::SETTINGS;
        }
        break;

      case ::GameState::GAME:
        //Map
        testMap.render(mapEditor.tileLibrary,window);
        //Collision display
        collisionCreator.render(window,collisionCreator.tileInstances);
        playerCar.getPhysics().drawDebug(window);
        aiCar.getPhysics().drawDebug(window);
        //Car Sprite
        window.draw(playerCar.getSprite());
        window.draw(aiCar.getSprite());
        //RPM Gauge
        RPMGauge.setVisible(true);
        RPMGauge.draw(window);
        //Check checkpoints
        checkpointHandler.checkIfInCheckpoints(playerCar);
        break;

      case ::GameState::SETTINGS:
        settingsMenu.update(mousePos,mousePressed);
        settingsMenu.draw(window);


        if (settingsMenu.stateSettings == 0) {
          mainMenu.stateSettings = 0;
          std::cout << "SETTING STATE TO MENU";
          currentState = ::GameState::MAIN_MENU;
        }
    }


    //Display
    window.display();
  }
}
