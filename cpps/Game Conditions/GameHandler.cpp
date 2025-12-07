//
// Created by M6XXY on 07/12/2025.
//

#include "GameHandler.h"

#include "AIController.h"
#include "CheckpointHandler.h"
#include "CollisionCreator.h"
#include "GameState.h"
#include "LoadSprites.h"
#include "MapEditor.h"
#include "Movement.h"
#include "PhysicsWorld.h"
#include "PlayerCar.h"
#include "../Car/CarSpecController.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/SettingsScene.h"
#include "../UI/rpmGauge.h"

GameHandler::GameHandler(sf::RenderWindow &window)
  : movement("../../keybinds.txt"),
    mainMenu(window),
    settingsMenu(window, movement),
    ai_controller(nullptr),
    playerCar(
      physics,
      spriteLoader,
      "../../assets/textures/placeholder-car.png",
      sf::Vector2f(1100.f, 200.f),
      carSpecController.makeTestCarSpec()
    ),
    aiCar(
      physics,
      spriteLoader,
      "../../assets/textures/placeholder-car.png",
      sf::Vector2f(1100.f, 230.f),
      carSpecController.makeTestCarSpec()
    ) {
}


void GameHandler::setup(sf::RenderWindow &window) {
  //MENU STATE
  int menuState = 0;
  //CORRECT STARTING
  float playerStartX = physics.toMeters(1100);
  float playerStartY = physics.toMeters(200);

  float aiStartX = physics.toMeters(1100);
  float aiStartY = physics.toMeters(230);

  //Rotate cars
  playerCar.getPhysics().getBody()->SetTransform({playerStartX,playerStartY},1.55);
  aiCar.getPhysics().getBody()->SetTransform({aiStartX,aiStartY},1.55);


  //Limit FPS
  window.setFramerateLimit(60);

  //Circle Object
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);



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



  //Load Map Editor

  b2Vec2 gravity(0.0f, 0.0f);
  b2World world(gravity);

  //Create Map
  int track[16][32] = {
    // Row 0
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    // Row 1
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    // Row 2
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    // Row 3
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,99,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    // Row 4
    {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    // Row 5
    {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    // Row 6
    {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    // Row 7
    {0,0,0,0,0,0,99,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    // Row 8
    {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0},
    // Row 9
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
    // Row 10
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0},
    // Row 11
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    // Row 12
    {0,0,0,1,99,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,99,0,0},
    // Row 13
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    // Row 14
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    // Row 15
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };




  // Set tiles in testMap
  for(int y = 0; y < 18; y++) {
    for(int x = 0; x < 32; x++) {
      testMap.setTile(track[y][x], x, y);
    }
  }
  checkpointHandler.init(testMap);

  constexpr float TILE_SIZE = 60.f;

  auto tileCenter = [TILE_SIZE](int tileX, int tileY) {
    return sf::Vector2f(tileX * TILE_SIZE + TILE_SIZE * 0.5f, tileY * TILE_SIZE + TILE_SIZE * 0.5f);
  };

  // TileX and TileY represent the map positions of waypoints for the ai to follow / Each map would have its own set
   aiPath = {
    tileCenter(15, 3), // Start Position
    tileCenter(8, 3),
    tileCenter(2, 2),
    tileCenter(1, 5),
    tileCenter(3, 5),
    tileCenter(6, 6),
    tileCenter(6, 8),
    tileCenter(3, 8),
    tileCenter(3, 12),
    tileCenter(5, 12),
    tileCenter(8, 13),
    tileCenter(24, 13),
    tileCenter(27, 14),
    tileCenter(29, 13),
    tileCenter(29, 10),
    tileCenter(26, 10),
    tileCenter(26, 8),
    tileCenter(29, 8),
    tileCenter(29, 3),
    tileCenter(15, 3), // Return to start
  };


  ai_controller = std::make_unique<AIController>(physics, aiPath, 11.f);


  //Create Collsion

  collisionCreator.createCollision(physics.world(), collisionCreator.tileCollisonVector, testMap);

  //Get Checkpoints



}

void GameHandler::start(sf::RenderWindow &window, GameState &currentState) {
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
          //Reset Race
          playerCar.reset();
          aiCar.reset();
          checkpointHandler.reset();
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
    MovementIntent aiIntent = ai_controller->update(aiCar.getPhysics(), dt);

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
        //collisionCreator.render(window,collisionCreator.tileInstances);
        playerCar.getPhysics().drawDebug(window);
        aiCar.getPhysics().drawDebug(window);
        //Car Sprite
        window.draw(playerCar.getSprite());
        window.draw(aiCar.getSprite());
        //RPM Gauge
        RPMGauge.setVisible(true);
        RPMGauge.draw(window);

        for (std::size_t i = 0; i < aiPath.size(); ++i) {

          // Draw waypoint as a yellow dot
          sf::CircleShape wp(5.f);
          wp.setFillColor(sf::Color::Yellow);
          wp.setOrigin(5.f, 5.f);
          wp.setPosition(aiPath[i]);
          window.draw(wp);

          // Draw a line to the next waypoint
          if (i + 1 < aiPath.size()) {
            sf::Vertex line[] = {
              sf::Vertex(aiPath[i],     sf::Color::Yellow),
              sf::Vertex(aiPath[i + 1], sf::Color::Yellow)
          };
            window.draw(line, 2, sf::Lines);
          }
        }
        //HUD
        hud.display(checkpointHandler,window);
        hud.update(checkpointHandler,window);
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