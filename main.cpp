#include <SFML/Graphics.hpp>
#include <../../../../header/movement.h>
#include <box2d/box2d.h>
#include "header/LoadSprites.h"
#include "header/PhysicsWorld.h"
#include "header/Player.h"

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
    window.draw(shape);
    window.draw(player.getSprite());
    window.display();
  }
}
