#include <SFML/Graphics.hpp>
#include <../../../../header/Movement.h>
#include <box2d/box2d.h>

#include "cpps/Game Conditions/CheckpointHandler.h"
#include "cpps/Game Conditions/GameHandler.h"
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



int main() {
  Global globalClass;
  //Create Window
  sf::RenderWindow window(sf::VideoMode({globalClass.resX, globalClass.resY}), "SFML works!");
  //Game Handler
  GameHandler game(window,globalClass);

  //Setup Game
  game.setup(window);

  //GAME LOOP
  while (window.isOpen()) {
    game.start(window,currentState);
  }
}
