#include "game.h"

game::game(Vector2u size, string title) {
    this->window.create(VideoMode(size.x, size.y), title);
	this->window.setFramerateLimit(60);
    
    update();
};

void game::drawWindow()
{
    window.clear();

    window.draw(shape);

    window.display();
}

void game::update()
{
    Event event;

    shape.setRadius(100.f);
    shape.setFillColor(sf::Color::Green);

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
