#include "game.h"
#include <map>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

game::game(Vector2u size, string title) {
    this->window.create(VideoMode(size.x, size.y), title);
	this->window.setFramerateLimit(60);

    wallTexture.loadFromFile("./Assets/wall.png");
    mainMenuTexture.loadFromFile("./Assets/mainMenu.png");
    plrTexture.loadFromFile("./Assets/playerExample.png");
    floorTexture.loadFromFile("./Assets/floorExample.png");
    voidTexture.loadFromFile("./Assets/voidExample.png");
    
    // 0 - void
    // 1 - stena
    // 2 - pod
    // 3 - klyuchalka
    // 4 - flagche

    textureMap = {
        {0, voidTexture},
        {1, wallTexture},
        {2, floorTexture}
    };

    level = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    loadLevel("1");
    plr.updatePos();
    plr.setTexture(plrTexture);
    plr.setPosition(Vector2f(640, 320));
    //MainMenu mainMenu(mainMenuTexture, Vector2f(0,0), window);
    update();
};

void game::loadLevel(string level) {
    fstream file("./Maps/maps.json");
    json data = json::parse(file);

    this->level = data[level];

    for (int i = 0; i < 9; i++) {
        tiles.push_back(vector<Tile>());

        for (int j = 0; j < 16; j++) {
            Tile tile;
            tile.setTexture(textureMap[this->level[i][j]]);
            tile.setPosition(Vector2f(j * 80.f, i * 80.f));

            tiles[i].push_back(tile);
        }
    }
}

void game::drawWindow()
{
    window.clear();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 16; j++) {
            tiles[i][j].draw(window);
        }
    }
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
        if(level[plr.playerTile.y][plr.playerTile.x-1] == 2)
        animatePlayerMovement(-80, 0);
    }
    else if (event.key.code == Keyboard::D) {
        if (level[plr.playerTile.y][plr.playerTile.x+1] == 2)
        animatePlayerMovement(80, 0);
    }
    else if (event.key.code == Keyboard::S) {
        if (level[plr.playerTile.y+1][plr.playerTile.x] == 2)
        animatePlayerMovement(0, 80);

    }
    else if (event.key.code == Keyboard::W) {
        if (level[plr.playerTile.y-1][plr.playerTile.x] == 2)
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