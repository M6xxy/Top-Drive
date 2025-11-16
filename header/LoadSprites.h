//
// Created by M6XXY on 16/11/2025.
//

#ifndef LOADSPRITES_H
#define LOADSPRITES_H
#include <string>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"


class LoadSprites {
public:
    void Load(sf::Sprite &sprite,sf::Texture& spriteTexture,const std::string& texturePath);
    void Draw(sf::RenderWindow& window, sf::Sprite& sprite);
private:

};



#endif //LOADSPRITES_H
