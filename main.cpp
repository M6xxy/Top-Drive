#include <SFML/Graphics.hpp>
#include <../../../../header/movement.h>
#include <box2d/box2d.h>

#include "cpps/Scenes/MenuScene.h"
#include "header/LoadSprites.h"
#include "header/PhysicsWorld.h"
#include "header/Player.h"

#include "header/CollisionCreator.h"
#include "header/LoadSprites.h"
#include "header/Map.h"
#include "header/MapEditor.h"

int main() {

  //MENU STATE
  int menuState = 0;
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


  // Cars Ground Body
  {
    b2BodyDef groundDef;
    groundDef.position.Set(physics.toMeters(400.f), physics.toMeters(750.f));
    b2Body* ground = physics.world().CreateBody(&groundDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(physics.toMeters(400.f), physics.toMeters(20.f));
    ground->CreateFixture(&groundBox, 0.0f);
  }

  // Car Visual Body
  sf::RectangleShape groundShape;
  groundShape.setSize({100.f, 40.f});
  groundShape.setOrigin(400.f, 20.f);
  groundShape.setPosition(400.f, 750.f);
  groundShape.setFillColor(sf::Color::Green);

  // Player
  Player player(
    physics,
    spriteLoader,
    "../../assets/textures/placeholder-car.png",
    {75, 75},
    5.0f // Speed in m/s
  );

  //Load Map Editor
  MapEditor mapEditor;
  b2Vec2 gravity(0.0f, 0.0f);
  b2World world(gravity);

  //Create Map
  int track[12][12] = {
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,0,0,0,0},
    {0,1,0,0,0,0,0,1,1,1,0,0},
    {0,1,1,1,1,1,0,0,0,1,0,0},
    {0,0,0,0,0,1,0,0,0,1,0,0},
    {0,1,1,1,0,1,0,0,0,1,0,0},
    {0,1,0,1,2,1,0,0,0,1,0,0},
    {0,1,0,1,1,1,0,0,0,1,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,2,1,1,1,1,2,1,0},
    {0,0,0,1,1,1,0,0,1,1,1,0},
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

  //Create Menu

  //Menu
  MenuScene mainMenu(window);

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

    // Intent VS physics
    player.updatePhysics(intent);
    physics.step(dt);

    // Physics visuals
    player.syncSpriteFromPhysics();

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

      //Player Sprite
      window.draw(player.getSprite());

      player.drawDebug(window);
    }


    //Display
    window.display();
  }
}
