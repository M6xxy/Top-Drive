//
// Created by M6XXY on 19/11/2025.
//

#ifndef MAP_H
#define MAP_H
#include <vector>

#include "Tile.h"
#include "SFML/Graphics/RenderWindow.hpp"


class Map {
public:
    std::vector<std::vector<int>> mapGrid;
    int maxHeight = 16;
    int maxWidth = 16;

    //Constructor
    Map();

    //Links tileID to Library and renders
    void render(std::vector<Tile> tileLibrary, sf::RenderWindow &window);
    void setTile(int id, int x ,int y);


private:
};



#endif //MAP_H
