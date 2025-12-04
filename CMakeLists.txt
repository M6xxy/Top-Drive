cmake_minimum_required(VERSION 3.11)
project(build_setup)

# Require modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Content
include(FetchContent)

# Setup Directories
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

# Fetch SFML
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

# Fetch Box2D
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)

FetchContent_MakeAvailable(box2d SFML)

# Add executable
add_executable(game
        main.cpp
        cpps/Movement.cpp
        cpps/loadSprites.cpp
        cpps/Player.cpp
        cpps/PhysicsWorld.cpp
        cpps/MapEditor.cpp
        cpps/Tile.cpp
        cpps/Map.cpp
        cpps/CollisionCreator.cpp
        cpps/CollisonBound.cpp
        header/loadSprites.h
        header/PhysicsWorld.h
        header/Player.h
        cpps/Player.cpp
        cpps/PhysicsWorld.cpp
        header/CarComponents.h
        cpps/CarComponents.cpp
        header/Car.h
        cpps/Car.cpp
        header/PlayerCar.h
        cpps/PlayerCar.cpp
        cpps/CarPhysics.cpp
        header/CarPhysics.h
        header/MapEditor.h
        header/Tile.h
        header/Map.h
        header/CollisionCreator.h
        header/CollisonBound.h
        cpps/UI/Button.cpp
        cpps/UI/Button.h
        cpps/UI/Menu.cpp
        cpps/UI/Menu.h
        cpps/Scenes/MenuScene.cpp
        cpps/Scenes/MenuScene.h
        "cpps/Game Conditions/CheckpointHandler.cpp"
        "cpps/Game Conditions/CheckpointHandler.h"
        cpps/Scenes/SettingsScene.cpp
        cpps/Scenes/SettingsScene.h
        "cpps/Game Conditions/GameState.cpp"
        "cpps/Game Conditions/GameState.h"
)

# Include directories
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/header)

# Link libraries
target_link_libraries(game
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        box2d

)
