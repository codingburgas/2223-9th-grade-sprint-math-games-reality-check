#include "game.h"
#include <map>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

game::game(Vector2u size, string title) {
    this->window.create(VideoMode(size.x, size.y), title);
	this->window.setFramerateLimit(60);

    this->voidTexture.loadFromFile("./Assets/void.png");
    this->wallTexture.loadFromFile("./Assets/wall.png");
    this->floorTexture.loadFromFile("./Assets/floor.png");
    this->boxTexture.loadFromFile("./Assets/exampleBox0.png");
    this->plrTexture.loadFromFile("./Assets/ORoperator.png");
    this->mainMenuTexture.loadFromFile("./Assets/mainMenu.png");
    
    // 0 - void
    // 1 - stena
    // 2 - pod
    // 3 - klyuchalka
    // 4 - flagche
    // 5 - kutiya

    textureMap = {
        {0, this->voidTexture},
        {1, this->wallTexture},
        {2, this->floorTexture}
    };

    Tile box;
    box.setTexture(boxTexture);
    box.setPosition(Vector2f(480, 240));
    attachedBoxes[0] = box;

    loadLevel("1");
    this->plr.setTexture(plrTexture);
    this->plr.setPosition(Vector2f(640, 240));
    //MainMenu mainMenu(mainMenuTexture, Vector2f(0,0), window);
    update();
};

void game::loadLevel(string level) {
    fstream file("./Maps/maps.json");
    json data = json::parse(file);

    this->level = data[level];

    for (int i = 0; i < 9; i++) {
        this->tiles.push_back(vector<Tile>());

        for (int j = 0; j < 16; j++) {
            Tile tile;
            tile.setTexture(textureMap[this->level[i][j]]);
            tile.setPosition(Vector2f(j * 80.f, i * 80.f));

            this->tiles[i].push_back(tile);
        }
    }
}

void game::drawWindow()
{
    this->window.clear();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 16; j++) {
            this->tiles[i][j].draw(this->window);
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if (this->attachedBoxes[i].exists()) {
            this->attachedBoxes[i].draw(this->window);
        }
    }
    
    this->plr.draw(this->window);

    this->window.display();
}

void game::update()
{
    while (this->window.isOpen())
    {
        while (this->window.pollEvent(this->event)) {
            if (this->event.type == Event::Closed) {
                this->window.close();
            }
            else {
                if (this->event.type == Event::KeyPressed) {
                    processKeyPressed();
                }
            }
        }
        drawWindow();
    }
}

void game::processKeyPressed() {
    if (this->event.key.code == Keyboard::A) {
        if (this->plr.playerTile.x - 1 >= 0) {
            if (this->level[this->plr.playerTile.y][this->plr.playerTile.x - 1] == 2) {
                for (int i = 0; i < 4; i++) {
                    if (this->attachedBoxes[i].exists()) {
                        if (this->attachedBoxes[i].position.x - 1 >= 0) {
                            if (this->level[this->attachedBoxes[i].position.y][this->attachedBoxes[i].position.x - 1] == 2) {
                                animatePlayerMovement(-80, 0);
                            }
                        }
                    }
                }

            }
        }
    }
    else if (this->event.key.code == Keyboard::D) {
        if (this->plr.playerTile.x + 1 <= 15) {
            if (this->level[this->plr.playerTile.y][this->plr.playerTile.x + 1] == 2) {
                for (int i = 0; i < 4; i++) {
                    if (this->attachedBoxes[i].exists()) {
                        if (this->attachedBoxes[i].position.x + 1 <= 15) {
                            if (this->level[this->attachedBoxes[i].position.y][this->attachedBoxes[i].position.x + 1] == 2) {
                                animatePlayerMovement(80, 0);
                            }
                        }
                    }
                }

            }
        }
    }
    else if (this->event.key.code == Keyboard::S) {
        if (this->plr.playerTile.y + 1 <= 8) {
            if (this->level[this->plr.playerTile.y + 1][this->plr.playerTile.x] == 2) {
                for (int i = 0; i < 4; i++) {
                    if (this->attachedBoxes[i].exists()) {
                        if (this->attachedBoxes[i].position.y + 1 <= 8) {
                            if (this->level[this->attachedBoxes[i].position.y + 1][this->attachedBoxes[i].position.x] == 2) {
                                animatePlayerMovement(0, 80);
                            }
                        }
                    }
                }
            }
        }
    }
    else if (this->event.key.code == Keyboard::W) {
        if (this->plr.playerTile.y - 1 >= 0) {
            if (this->level[this->plr.playerTile.y - 1][this->plr.playerTile.x] == 2) {
                for (int i = 0; i < 4; i++) {
                    if (this->attachedBoxes[i].exists()) {
                        if (this->attachedBoxes[i].position.y - 1 >= 0) {
                            if (this->level[this->attachedBoxes[i].position.y - 1][this->attachedBoxes[i].position.x] == 2) {
                                animatePlayerMovement(0, -80);
                            }
                        }
                    }
                }
            }
        }

    }
}

void game::animatePlayerMovement(int xChange, int yChange) {
    if (xChange < 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            this->plr.move(Vector2f(-16, 0));
            
            for (int i = 0; i < 2; i++) {
                if (this->attachedBoxes[i].exists()) {
                    this->attachedBoxes[i].move(Vector2f(-16, 0));

                }
            }
        }
    }
    else if (xChange > 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            this->plr.move(Vector2f(16, 0));

            for (int i = 0; i < 2; i++) {
                this->attachedBoxes[i].move(Vector2f(16, 0));
            }
        }
    }
    if (yChange < 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            this->plr.move(Vector2f(0, -16));

            for (int i = 0; i < 2; i++) {
                this->attachedBoxes[i].move(Vector2f(0, -16));
            }
        }
    }
    else if (yChange > 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            this->plr.move(Vector2f(0, 16));

            for (int i = 0; i < 2; i++) {
                this->attachedBoxes[i].move(Vector2f(0, 16));
            }
        }
    }
}