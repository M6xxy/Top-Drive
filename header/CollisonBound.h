//
// Created by M6XXY on 23/11/2025.
//

#ifndef COLLISONBOUND_H
#define COLLISONBOUND_H
#include "box2d/b2_math.h"


class b2Body;

class CollisonBound {
public:
    int tileId = 0;
    b2Vec2 verteciesPart1[4];
    b2Vec2 verteciesPart2[4];
    b2Body* body = nullptr;

};



#endif //COLLISONBOUND_H
