//
// Created by M6XXY on 07/12/2025.
//

#ifndef HUD_H
#define HUD_H
#include "../cpps/Game Conditions/CheckpointHandler.h"


class Hud {
public:
    Hud();

    void display(CheckpointHandler& checkpointHandler, sf::RenderWindow &window);

    void update(CheckpointHandler &ch, sf::RenderWindow &window);

    void Render(CheckpointHandler &ch, sf::RenderWindow &window);

private:
    sf::Font font;
    sf::Text lapText;
    sf::Text checkPointText;
    int lcurrCheckpoint = 1;
};



#endif //HUD_H
