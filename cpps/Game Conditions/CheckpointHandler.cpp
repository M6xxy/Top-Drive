//
// Created by M6XXY on 25/11/2025.
//

#include "CheckpointHandler.h"

#include <iostream>
#include <ostream>


#include "GameState.h"
#include "Map.h"
#include "PlayerCar.h"

const float SCALE = 30.0f;  // 30 pixels = 1 meter
const float TILE_SIZE = 60.0f;         // pixels
const float HALF_TILE = TILE_SIZE / 2.0f / SCALE; // 1 meter

void CheckpointHandler::populateCheckpointList(Map& map) {
    //Go through each tile on map and add checkpoint tiles to list
    for (int y = 0; y < map.maxHeight; y++) {
        for (int x = 0; x < map.maxWidth; x++) {
            //If tile is checkpoint coords add to list
            if (map.mapGrid[y][x] == 99) {
                this->checkpointList.push_back({x,y});
            }
        }
    }
}

void CheckpointHandler::displayCheckpointListDebug() {
    for (const auto& cp : checkpointList) {
        std::cout << "Checkpoint at x=" << cp.x
                  << ", y=" << cp.y << std::endl;
    }

    std::cout << "FIRST CHECKPOINT AT X:" << checkpointList.at(currCheckpoint).x << " Y: " << checkpointList.at(currCheckpoint).y;

}

void CheckpointHandler::checkpointDataSetup() {
    //Set checkpoints to 1
    this->currCheckpoint = 0;
    this->totalCheckpoints = this->checkpointList.size() + 1;
    this->lapCount = 0;

}

void CheckpointHandler::checkIfInCheckpoints(PlayerCar &car, GameState &currState) {

    //Get location of car
    b2Vec2 carPosMeters = car.getPhysics().getBody()->GetPosition();

    //Convert to pixels
    float pixelPosX = carPosMeters.x * SCALE;
    float pixelPosY = carPosMeters.y * SCALE;

    //Get current tile coords
    int currTileX = static_cast<int>(std::floor(pixelPosX / TILE_SIZE));
    int currTileY = static_cast<int>(std::floor(pixelPosY / TILE_SIZE));

    //Check if tile is in current Checkpoint
    if (this->checkpointList.at(currCheckpoint).x == currTileX && this->checkpointList.at(currCheckpoint).y == currTileY) {
        std::cout << "\n Checkpoint Crossed AT: X" << checkpointList.at(currCheckpoint).x << " Y:" <<  checkpointList.at(currCheckpoint).y;
        currCheckpoint++;

        //Check if checkpoint overflow
        if (currCheckpoint >= this->checkpointList.size()) {
            currCheckpoint = 0;
        }

        if (currCheckpoint == 1) {
            lapCount++;
            std::cout << "LAP FINISHED CURR LAP: " << lapCount;
        }

        std::cout << "\n Next Checkpoint AT: X" << checkpointList.at(currCheckpoint).x << " Y:" <<  checkpointList.at(currCheckpoint).y;
    }

    //Win/Lose
    if (lapCount > 1) {
        lapCount = 0;
        currCheckpoint = 0;
        currState = GameState::POSTGAME;

    }
}

void CheckpointHandler::init(Map &map) {
        populateCheckpointList(map);
        checkpointDataSetup();      // set currCheckpoint, lap, etc.

        if (!checkpointList.empty()) {
            displayCheckpointListDebug();
        }
}

void CheckpointHandler::reset() {
    lapCount = 0;
    currCheckpoint = 0;
}



