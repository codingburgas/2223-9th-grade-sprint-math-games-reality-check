#include "game.h"

game::game(Vector2u size, string title) {
    this->window.create(VideoMode(size.x, size.y), title);
	this->window.setFramerateLimit(60);
    
    update();
};

void game::drawWindow()
{
    window.clear();
    window.draw(this->mainLevel.level);
    // TODO: Add drawing of each component of big level


    //window.draw(this->shape);
    window.display();
}

void game::update()
{
    Event event;
    this->mainLevel.init();

    while (this->window.isOpen())
    {
        while (this->window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        drawWindow();
    }
}

