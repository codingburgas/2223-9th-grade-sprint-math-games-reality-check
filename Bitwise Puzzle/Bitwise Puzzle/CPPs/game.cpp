#include "game.h"

game::game(Vector2u size, string title) {
    this->window.create(VideoMode(size.x, size.y), title);
	this->window.setFramerateLimit(60);

    tileTexture.loadFromFile("./Assets/example.png");

    for (int i = 0; i < 9; i++) {
        tiles.push_back(vector<Tile>());
        for (int j = 0; j < 16; j++) {
            Tile tile;
            tile.setTexture(tileTexture);
            tile.setPosition(Vector2f(j * 80.f, i * 80.f));
        
            tiles[i].push_back(tile);
        }
    }
    
    update();
};

void game::drawWindow()
{
    window.clear();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 16; j++) {
            tiles[i][j].draw(window);
        }
    }

    window.display();
}

void game::update()
{
    Event event;

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
