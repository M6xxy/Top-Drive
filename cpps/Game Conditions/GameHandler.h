// GameHandler.h
//
// Created by M6XXY on 07/12/2025.
//

#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <vector>
#include <memory>

#include "AIController.h"
#include "CheckpointHandler.h"
#include "CollisionCreator.h"
#include "GameState.h"
#include "LoadSprites.h"
#include "MapEditor.h"
#include "Movement.h"
#include "PlayerCar.h"
#include "../Car/CarSpecController.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/SettingsScene.h"
#include "../UI/Hud.h"
#include "../UI/rpmGauge.h"

class GameHandler {
public:
    GameHandler(sf::RenderWindow &window);
    void setup(sf::RenderWindow &window);
    void start(sf::RenderWindow &window, GameState &currentState);

private:
    // Core dependencies
    Movement movement;
    LoadSprites spriteLoader;
    PhysicsWorld physics;
    CarSpecController carSpecController;

    std::vector<sf::Vector2f> aiPath;

    // UI / scenes
    MenuScene mainMenu;
    SettingsScene settingsMenu;
    rpmGauge RPMGauge;

    // runtime/clock
    sf::Clock dt_clock;

    // controllers & game objects
    // Make AI controller a pointer so we can construct it after aiPath is filled in setup()
    std::unique_ptr<AIController> ai_controller;

    PlayerCar playerCar;
    PlayerCar aiCar;

    CollisionCreator collisionCreator;
    Map testMap;
    CheckpointHandler checkpointHandler;
    MapEditor mapEditor;
    Hud hud;
};

#endif //GAMEHANDLER_H
