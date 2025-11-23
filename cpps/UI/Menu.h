//
// Created by M6XXY on 23/11/2025.
//

#ifndef MENU_H
#define MENU_H
#include "Button.h"


class Menu {
public:


    void addButton(Button button);

    void draw(sf::RenderWindow &window);

    void update(sf::Vector2f mousePos, bool mousePressed);
private:
    std::vector<Button> buttonList;

};



#endif //MENU_H
