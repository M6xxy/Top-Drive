//
// Created by M6XXY on 19/11/2025.
//

#ifndef TILE_H
#define TILE_H
#include <string>

#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include "box2d/b2_polygon_shape.h"


class Tile {
public:
    int ID = 0;
    std::string name = "Null";
    b2Body* body = nullptr;
    int grip = 0.1f;
};



#endif //TILE_H
