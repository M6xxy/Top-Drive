//
// Created by M6XXY on 19/11/2025.
//

#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include <vector>

#include "Tile.h"


class Tile;

class MapEditor {
public:
    //Vector of tile objects
    std::vector<Tile> tileLibrary;


    // Load tiledata on creation
    MapEditor() {
        loadTileLibrary();
    }
private:
    //Holds all tile data
    void loadTileLibrary() {
        //Tile 1
        Tile track;
        track.ID = 0;
        track.grip = 1.0f;
        track.name = "Track Tile";

        tileLibrary.push_back(track);
        //Tile 2
        Tile grass;
        grass.ID = 1;
        grass.grip = 1.0f;
        grass.name = "Grass Tile";

        tileLibrary.push_back(grass);

        //Tile 3
        Tile cornerTop;
        cornerTop.ID = 2;
        cornerTop.grip = 1.0f;
        cornerTop.name = "Corner Top Tile";

        tileLibrary.push_back(cornerTop);

        //Tile  4
        Tile cornerLeft;
        cornerLeft.ID = 3;
        cornerLeft.grip = 1.0f;
        cornerLeft.name = "Corner Left Tile";

        tileLibrary.push_back(cornerLeft);

        //Tile 5
        Tile cornerRight;
        cornerRight.ID = 4;
        cornerRight.grip = 1.0f;
        cornerRight.name = "Corner Right Tile";

        tileLibrary.push_back(cornerRight);

        //Tile 6
        Tile cornerBottom;
        cornerBottom.ID = 5;
        cornerBottom.grip = 1.0f;
        cornerBottom.name = "Corner Bottom Tile";

        tileLibrary.push_back(cornerBottom);

        // Tile 7 - Checkpoint
        Tile checkpoint;
        checkpoint.ID = 99;
        checkpoint.name = "Checkpoint Tile";
        checkpoint.grip = 1.0f;
        checkpoint.isCheckpoint = true;
    }
};



#endif //MAPEDITOR_H
