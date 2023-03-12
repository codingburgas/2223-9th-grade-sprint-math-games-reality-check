#include "game.h"

game::game(Vector2u size, string title) {
    this->window.create(VideoMode(size.x, size.y), title);
	this->window.setFramerateLimit(60);

    tileTexture.loadFromFile("./Assets/wall.png");
    mainMenuTexture.loadFromFile("./Assets/mainMenu.png");
    plrTexture.loadFromFile("./Assets/playerExample.png");

    for (int i = 0; i < 9; i++) {
        tiles.push_back(vector<Tile>());
     
        for (int j = 0; j < 16; j++) {
            Tile tile;
            tile.setTexture(tileTexture);
            tile.setPosition(Vector2f(j * 80.f, i * 80.f));
        
            tiles[i].push_back(tile);
        }
    }

    plr.updatePos();
    plr.setTexture(plrTexture);

    //MainMenu mainMenu(mainMenuTexture, Vector2f(0,0), window);
    update();
};

void game::drawWindow()
{
    window.clear();

    /*for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 16; j++) {
            tiles[i][j].draw(window);
        }
    }*/

    plr.draw(window);

    window.display();
}

void game::update()
{
    while (this->window.isOpen())
    {
        while (this->window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else {
                if (event.type == Event::KeyPressed) {
                    processKeyPressed();
                }
            }
        }
        drawWindow();
    }
}


void game::processKeyPressed() {
    if (event.key.code == Keyboard::A) {
        animatePlayerMovement(-80, 0);
    }
    else if (event.key.code == Keyboard::D) {
        animatePlayerMovement(80, 0);
    }
    else if (event.key.code == Keyboard::S) {
        animatePlayerMovement(0, 80);

    }
    else if (event.key.code == Keyboard::W) {
        animatePlayerMovement(0, -80);

    }
}

void game::animatePlayerMovement(int xChange, int yChange) {
    if (xChange < 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            plr.move(Vector2f(-16, 0));
        }
    }
    else if (xChange > 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            plr.move(Vector2f(16, 0));
        }
    }
    if (yChange < 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            plr.move(Vector2f(0, -16));
        }
    }
    else if (yChange > 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            plr.move(Vector2f(0, 16));
        }
    }
}