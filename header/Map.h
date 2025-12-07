//
// Created by M6XXY on 19/11/2025.
//

#ifndef MAP_H
#define MAP_H
#include <vector>

#include "Tile.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>


class Map {
public:
    std::vector<std::vector<int>> mapGrid;
    int maxHeight = 18;
    int maxWidth = 32;

    //Constructor
    Map();

    //Links tileID to Library and renders
    void render(std::vector<Tile> tileLibrary, sf::RenderWindow &window);
    void setTile(int id, int x ,int y);


private:
    sf::Texture track;
    sf::Sprite trackSprite;
    sf::Texture bounds;
    sf::Sprite boundSprite;
    sf::Texture grass;
    sf::Sprite grassSprite;
    sf::Texture checkpoint;
    sf::Sprite checkpointSprite;
};



#endif //MAP_H
