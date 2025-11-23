#include <SFML/Graphics.hpp>
#include <../../../../header/movement.h>
#include <box2d/box2d.h>
#include "header/LoadSprites.h"
#include "header/PhysicsWorld.h"
#include "header/Player.h"

#include "header/CollisionCreator.h"
#include "header/LoadSprites.h"
#include "header/Map.h"
#include "header/MapEditor.h"

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
  groundShape.setSize({800.f, 40.f});
  groundShape.setOrigin(400.f, 20.f);
  groundShape.setPosition(400.f, 750.f);
  groundShape.setFillColor(sf::Color::Green);

  // Player
  Player player(
    physics,
    spriteLoader,
    "../../assets/textures/placeholder-car.png",
    {400.f, 200.f},
    5.0f // Speed in m/s
  );
  //Load Map Editor
  MapEditor mapEditor;
  b2Vec2 gravity(0.0f, 0.0f);
  b2World world(gravity);

  //Create Map
  Map testMap;
  testMap.setTile(1,0,0);
  testMap.setTile(1,1,0);
  testMap.setTile(0,2,0);
  testMap.setTile(1,3,0);

  //Create Collsion
  CollisionCreator collisionCreator;
  collisionCreator.createCollision(physics.world(),collisionCreator.tileCollisonVector,testMap);


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

    // Intent VS physics
    player.updatePhysics(intent);
    physics.step(dt);





    // Physics visuals
    player.syncSpriteFromPhysics();

    // 4. Render
    window.clear();
    //Map
    testMap.render(mapEditor.tileLibrary,window);
    //Collision display
    collisionCreator.render(window,collisionCreator.tileInstances);

    //Player Sprite
    window.draw(player.getSprite());

    //window.draw(shape);
   // spriteLoader.Draw(window,playerSprite);


    //Display
    window.display();
  }
}
