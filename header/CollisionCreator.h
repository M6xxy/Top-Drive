//
// Created by M6XXY on 23/11/2025.
//

#ifndef COLLISIONCREATOR_H
#define COLLISIONCREATOR_H
#include <vector>

#include "CollisonBound.h"
#include "Map.h"
#include "../cmake-build-debug-coverage/_deps/box2d-src/include/box2d/b2_world.h"

const float PIXELS_PER_METER = 30.0f;  // 30 pixels = 1 meter
const float TILE_SIZE = 60.0f;         // pixels
const float HALF_TILE = TILE_SIZE / 2.0f / PIXELS_PER_METER; // 1 meter


class CollisionCreator {
public:
    //Varibles
    std::vector<CollisonBound> tileCollisonVector;
    std::vector<CollisonBound> tileInstances;

    //Constructor
    CollisionCreator() {
        loadCollisionLibrary();
    }

    //Methods
    void createCollision(b2World &world, std::vector<CollisonBound> &collisionList, Map &map);
    void render(sf::RenderWindow& window, const std::vector<CollisonBound>& collisionList);
private:
    void loadCollisionLibrary() {
        //Tile 1
        CollisonBound track;
        track.tileId = 0;
        //Shape 1
        track.verteciesPart1[0].Set(-1.0f, -1.0f);  // bottom-left
        track.verteciesPart1[1].Set( 1.0f, -1.0f);  // bottom-right
        track.verteciesPart1[2].Set( 1.0f,  1.0f);  // top-right
        track.verteciesPart1[3].Set(-1.0f,  1.0f);  // top-left
        //Shape 2
        track.verteciesPart2[0].Set(-0.5f, 0.0f);
        track.verteciesPart2[1].Set(-0.5f, 1.0f);
        track.verteciesPart2[2].Set( 1.0f, 1.0f);
        track.verteciesPart2[3].Set( 1.0f, 0.0f);

        //Add to vector
        tileCollisonVector.push_back(track);
    }
};



#endif //COLLISIONCREATOR_H
