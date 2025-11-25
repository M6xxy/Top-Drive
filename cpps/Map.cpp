//
// Created by M6XXY on 19/11/2025.
//

#include "../header/Map.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

//Constructor
Map::Map() {
        mapGrid.resize(maxHeight, std::vector<int>(maxWidth, 0));
}
//Rendering
void Map::render(std::vector<Tile> tileLibrary, sf::RenderWindow& window) {
    //SIZE OF TILE
    const int TILE_SIZE = 60;

    //Test Square
    sf::RectangleShape tileRect(sf::Vector2f(TILE_SIZE,TILE_SIZE));


    // ADVANCE Y AND X
    for (int y = 0; y < maxHeight; y++) {
        for (int x = 0; x < maxWidth;x++) {

            //Get ID of each tile and render
            int id =mapGrid[y][x];
            Tile& t = tileLibrary[id];
            //Check if id = 1
            if (id > 0 && id < 80) {
                tileRect.setFillColor(sf::Color::Green);
            } else {
                tileRect.setFillColor(sf::Color::Red);
            }
            // If checkpoint
            if (id == 99) {
                tileRect.setFillColor(sf::Color::Yellow);
            }
            //Set tile
            tileRect.setPosition(x * TILE_SIZE, y * TILE_SIZE);

            window.draw(tileRect);

        }
    }
}

void Map::setTile(int id, int x,int y) {
    //Validation make sure tile not out of bounds
    if (y < 0 || y >= maxHeight) return;
    if (x < 0 || x >= maxWidth) return;

    mapGrid[y][x] = id;
}