//
// Created by M6XXY on 19/11/2025.
//

#include "../header/Map.h"

#include <iostream>
#include <ostream>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>

//Constructor
Map::Map() {
    mapGrid.resize(maxHeight, std::vector<int>(maxWidth, 0));

    // ----- Textures
    //Track
    if (!track.loadFromFile("../../assets/textures/track.png")) {
        std::cerr << "Failed to load track texture!" << std::endl;
    }
    trackSprite.setTexture(track);

    //Grass
    if (!grass.loadFromFile("../../assets/textures/grass.png")) {
        std::cerr << "Failed to load track texture!" << std::endl;
    }
    grassSprite.setTexture(grass);

    //Checkpoint
    if (!checkpoint.loadFromFile("../../assets/textures/checkpoint.png")) {
        std::cerr << "Failed to load track texture!" << std::endl;
    }
    checkpointSprite.setTexture(checkpoint);
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
            if (id == 1) {
                trackSprite.setTextureRect(sf::IntRect(0,0,60,60));
                trackSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                window.draw(trackSprite);
            }
            //Grass
            if (id == 0) {
                grassSprite.setTextureRect(sf::IntRect(0,0,60,60));
                grassSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                window.draw(grassSprite);
            }
            // If checkpoint
            if (id == 99) {
                checkpointSprite.setTextureRect(sf::IntRect(0,0,60,60));
                checkpointSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                window.draw(checkpointSprite);
            }
            //Set tile
            tileRect.setPosition(x * TILE_SIZE, y * TILE_SIZE);



        }
    }
}

void Map::setTile(int id, int x,int y) {
    //Validation make sure tile not out of bounds
    if (y < 0 || y >= maxHeight) return;
    if (x < 0 || x >= maxWidth) return;

    mapGrid[y][x] = id;
}