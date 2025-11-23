#include <SFML/Graphics.hpp>
#include <../../../../header/movement.h>

#include "header/CollisionCreator.h"
#include "header/LoadSprites.h"
#include "header/Map.h"
#include "header/MapEditor.h"

int main() {
  //DECLERATIONS N STUFF
  LoadSprites spriteLoader;

  //DELTA CLOCK
  sf:
    sf::Clock dt_clock;

  //Create Window
  sf::RenderWindow window(sf::VideoMode({800, 800}), "SFML works!");

  //Limit FPS
  window.setFramerateLimit(60);

  //Circle Object
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  //Sprite
  sf::Sprite playerSprite;
  sf::Texture player_texture;
  spriteLoader.Load(playerSprite,player_texture,"../../assets/textures/placeholder-car.png");

  //Movement Setup
  Movement movement(playerSprite,50.f);

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
  collisionCreator.createCollision(world,collisionCreator.tileCollisonVector,testMap);


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

    // 3. Update movement
    movement.update(dt);

    // 4. Render
    window.clear();

    //window.draw(shape);
   // spriteLoader.Draw(window,playerSprite);

    //Map
    testMap.render(mapEditor.tileLibrary,window);

    //Collision display
    collisionCreator.render(window,collisionCreator.tileInstances);

    //Display
    window.display();
  }
}
