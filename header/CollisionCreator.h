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

        // Square 2 (Part2) - overlapping same size
        track.verteciesPart2[0].Set(-1.0f, -1.0f);  // bottom-left
        track.verteciesPart2[1].Set( 1.0f, -1.0f);  // bottom-right
        track.verteciesPart2[2].Set( 1.0f,  1.0f);  // top-right
        track.verteciesPart2[3].Set(-1.0f,  1.0f);  // top-left

        //Add to vector
        tileCollisonVector.push_back(track);

        //Tile 2
        CollisonBound cornerTop;
        cornerTop.tileId = 2;
        //Shape 1
        cornerTop.verteciesPart1[0].Set(-1.0f, -1.0f);
        cornerTop.verteciesPart1[1].Set( 1.0f, -1.0f);
        cornerTop.verteciesPart1[2].Set( 1.0f,  0.0f);
        cornerTop.verteciesPart1[3].Set(-1.0f,  0.0f);

        // Top trapezoid (narrower at the top)
        cornerTop.verteciesPart2[0].Set(-1.f, 0.0f);   // bottom-left of trapezoid
        cornerTop.verteciesPart2[1].Set( 1.f, 0.0f);   // bottom-right of trapezoid
        cornerTop.verteciesPart2[2].Set( 0.5f, 0.6f);   // top-right of trapezoid
        cornerTop.verteciesPart2[3].Set(-0.5f, 0.6f);   // top-left of trapezoid

        //Add to vector
        tileCollisonVector.push_back(cornerTop);

        //Tile 3
        CollisonBound cornerLeft;
        cornerLeft.tileId = 3;
        //Shape 1
        cornerLeft.verteciesPart1[0].Set( 1.0f, -1.0f);
        cornerLeft.verteciesPart1[1].Set( 1.0f,  1.0f);
        cornerLeft.verteciesPart1[2].Set( 0.0f,  1.0f);
        cornerLeft.verteciesPart1[3].Set( 0.0f, -1.0f);

        cornerLeft.verteciesPart2[0].Set( 0.0f, -1.0f);
        cornerLeft.verteciesPart2[1].Set( 0.0f,  1.0f);
        cornerLeft.verteciesPart2[2].Set(-0.6f, 0.5f);
        cornerLeft.verteciesPart2[3].Set(-0.6f, -0.5f);

        //Add to vector
        tileCollisonVector.push_back(cornerLeft);

        //Tile 3
        CollisonBound cornerRight;
        cornerRight.tileId = 4;
        //Shape 1
        cornerRight.verteciesPart1[0].Set(-1.0f,  1.0f);
        cornerRight.verteciesPart1[1].Set(-1.0f, -1.0f);
        cornerRight.verteciesPart1[2].Set( 0.0f, -1.0f);
        cornerRight.verteciesPart1[3].Set( 0.0f,  1.0f);

        cornerRight.verteciesPart2[0].Set(0.0f,  1.0f);
        cornerRight.verteciesPart2[1].Set(0.0f, -1.0f);
        cornerRight.verteciesPart2[2].Set(0.6f, -0.5f);
        cornerRight.verteciesPart2[3].Set(0.6f,  0.5f);

        //Add to vector
        tileCollisonVector.push_back(cornerRight);

        //Tile 3
        CollisonBound cornerBottom;
        cornerBottom.tileId = 5;
        //Shape 1
        cornerBottom.verteciesPart1[0].Set( 1.0f,  1.0f);
        cornerBottom.verteciesPart1[1].Set(-1.0f,  1.0f);
        cornerBottom.verteciesPart1[2].Set(-1.0f,  0.0f);
        cornerBottom.verteciesPart1[3].Set( 1.0f,  0.0f);

        cornerBottom.verteciesPart2[0].Set( 1.0f,  0.0f);
        cornerBottom.verteciesPart2[1].Set(-1.0f,  0.0f);
        cornerBottom.verteciesPart2[2].Set(-0.5f, -0.6f);
        cornerBottom.verteciesPart2[3].Set( 0.5f, -0.6f);
        //Add to vector
        tileCollisonVector.push_back(cornerBottom);
    }
};



#endif //COLLISIONCREATOR_H
