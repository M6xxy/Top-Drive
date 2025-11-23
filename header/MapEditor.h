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
        Tile corner;
        corner.ID = 2;
        corner.grip = 1.0f;
        corner.name = "Corner Top Tile";

        tileLibrary.push_back(corner);
    }
};



#endif //MAPEDITOR_H
