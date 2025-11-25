//
// Created by M6XXY on 25/11/2025.
//

#ifndef CHECKPOINTHANDLER_H
#define CHECKPOINTHANDLER_H
#include <vector>

#include "Map.h"
#include "PlayerCar.h"
#include "Tile.h"

struct CheckpointCoords {
    int x;
    int y;
};

class CheckpointHandler {
public:
    std::vector<CheckpointCoords> checkpointList;
    int currCheckpoint = 0;
    int totalCheckpoints = 0;
    int lapCount = 0;

    //Constrcutor
    explicit CheckpointHandler(Map &map) {
        populateCheckpointList(map);
        displayCheckpointListDebug();
    }

    void checkIfInCheckpoints(PlayerCar &car);
private:
    void populateCheckpointList(Map &map);
    void addLap();
    void displayCheckpointListDebug();
    void checkpointDataSetup();

};



#endif //CHECKPOINTHANDLER_H
