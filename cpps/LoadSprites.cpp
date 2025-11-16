//
// Created by M6XXY on 16/11/2025.
//

#include "../header/LoadSprites.h"
#include "SFML/Graphics/Texture.hpp"

void LoadSprites::Load(sf::Sprite &sprite, sf::Texture& spriteTexture,const std::string& texturePath) {
    spriteTexture.loadFromFile(texturePath);
    sprite.setTexture(spriteTexture);
    sprite.setPosition(200.f,200.f);
}

void LoadSprites::Draw(sf::RenderWindow& window, sf::Sprite& sprite) {
    window.draw(sprite);
}
