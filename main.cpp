#include <SFML/Graphics.hpp>
#include <../../../../header/movement.h>

int main() {
  //DECLERATIONS N STUFF
  //DELTA CLOCK
  sf:
    sf::Clock dt_clock;

  sf::RenderWindow window(sf::VideoMode({800, 800}), "SFML works!");
  //Circle Object
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  //Movement Setup
  Movement movement(shape,50.f);


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
    window.draw(shape);
    window.display();
  }
}