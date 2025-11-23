//
// Created by M6XXY on 23/11/2025.
//

#include "../header/CollisionCreator.h"

#include "../cmake-build-debug-coverage/_deps/sfml-src/include/SFML/Graphics/ConvexShape.hpp"
#include "../header/Map.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
void CollisionCreator::createCollision(b2World &world, std::vector<CollisonBound> &collisionList, Map& map) {
        //Store all tiles


    //Go through each Y and X on Grid
    for (int y = 0; y < map.maxHeight;y++) {
        for (int x = 0; x < map.maxWidth;x++) {
            //Get tile iD
            int tileID = map.mapGrid[y][x];

            //Go into collsionList and generate collisonBox
            for (int i = 0; i < collisionList.size(); i++) {
                //Verify that ID match if so create bounds
                if (tileID == collisionList[i].tileId) {
                    CollisonBound tileBound = collisionList[i];

                    //Get center of tile
                    float tilePosX = (x * TILE_SIZE + TILE_SIZE / 2.0f) / PIXELS_PER_METER;
                    float tilePosY = (y * TILE_SIZE + TILE_SIZE / 2.0f) / PIXELS_PER_METER;

                    //Create Static Body
                    b2BodyDef bodyDef;
                    bodyDef.type = b2_staticBody;
                    bodyDef.position.Set(tilePosX,tilePosY);

                    //Create and assign
                    b2Body* body = world.CreateBody(&bodyDef);
                    tileBound.body = body;

                    //Create shape
                    b2PolygonShape shape1;
                    shape1.Set(collisionList[i].verteciesPart1,4);

                    body->CreateFixture(&shape1,0.0f);

                    b2PolygonShape shape2;
                    shape2.Set(collisionList[i].verteciesPart2,4);

                    body->CreateFixture(&shape2,0.0f);

                    //Store tile
                    tileInstances.push_back(tileBound);
                }
            }
        }
    }
}
void CollisionCreator::render(sf::RenderWindow &window, const std::vector<CollisonBound> &collisionList) {
    const float PIXELS_PER_METER = 30.0f;

    for (const auto& bound : collisionList) {
        if (!bound.body) continue;

        for (b2Fixture* f = bound.body->GetFixtureList(); f; f = f->GetNext()) {
            if (f->GetType() != b2Shape::e_polygon) continue;

            b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
            sf::ConvexShape polygon;
            polygon.setPointCount(shape->m_count);

            for (int i = 0; i < shape->m_count; i++) {
                b2Vec2 worldPoint = bound.body->GetWorldPoint(shape->m_vertices[i]);
                polygon.setPoint(i, sf::Vector2f(worldPoint.x * PIXELS_PER_METER,
                                                 worldPoint.y * PIXELS_PER_METER));
            }

            polygon.setFillColor(sf::Color(0,0,255,100));
            polygon.setOutlineColor(sf::Color::Blue);
            polygon.setOutlineThickness(1.0f);

            window.draw(polygon);
        }
    }
}


