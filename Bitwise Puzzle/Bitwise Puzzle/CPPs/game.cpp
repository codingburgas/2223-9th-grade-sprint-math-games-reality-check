#include "game.h"
#include <map>
#include "json.hpp"
#include <fstream>
#include <thread>

using json = nlohmann::json;

game::game(Vector2u size, string title) {
    this->window.create(VideoMode(size.x, size.y), title);
	this->window.setFramerateLimit(60);

    this->voidTexture.loadFromFile("./Assets/void.png");
    this->wallTexture.loadFromFile("./Assets/wall.png");
    this->floorTexture.loadFromFile("./Assets/floor.png");
    this->box0Texture.loadFromFile("./Assets/Box0.png");
    this->box1Texture.loadFromFile("./Assets/Box1.png");
    this->plrTexture.loadFromFile("./Assets/ORoperator.png");
    this->mainMenuTexture.loadFromFile("./Assets/mainMenu.png");
    this->lock0Texture.loadFromFile("./Assets/Lock0.png");
    this->lock1Texture.loadFromFile("./Assets/Lock1.png");
    
    // 0 - void
    // 1 - stena
    // 2 - pod
    // 3 - flagche
    // 4 - klyuchalka 0
    // 5 - klyuchalka 1
    // 6 - kutiya 0
    // 7 - kutiya 1

    textureMap = {
        {0, this->voidTexture},
        {1, this->wallTexture},
        {2, this->floorTexture},
        {4, this->lock0Texture},
        {5, this->lock1Texture},
        {6, this->box0Texture},
        {7, this->box1Texture}
    };

    loadLevel("1");
    this->plr.setTexture(plrTexture);
    this->plr.setPosition(Vector2f(640, 240));

    this->canMove = true;
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
            if (this->level[i][j] < 3) {
                Tile tile;
                tile.setTexture(textureMap[this->level[i][j]]);
                tile.setPosition(Vector2f(j * 80.f, i * 80.f));

                this->tiles[i].push_back(tile);
            }
            else if (this->level[i][j] == 4 || this->level[i][j] == 5) {
                Tile tile;
                tile.setTexture(textureMap[2]);
                tile.setPosition(Vector2f(j * 80.f, i * 80.f));
                
                this->tiles[i].push_back(tile);

                CustomLock lock;
                lock.setTexture(textureMap[this->level[i][j]]);
                lock.setPosition(Vector2f(j * 80.f, i * 80.f));

                this->locks.push_back(lock);
            }
            else if (this->level[i][j] == 6 || this->level[i][j] == 7) {
                Tile tile;
                tile.setTexture(textureMap[2]);
                tile.setPosition(Vector2f(j * 80.f, i * 80.f));
                
                this->tiles[i].push_back(tile);

                Box box;
                box.setTexture(textureMap[this->level[i][j]]);
                box.setPosition(Vector2f(j * 80.f, i * 80.f));

                this->boxes.push_back(box);
            }
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
    
    for (int i = 0; i < boxes.size(); i++) {
        this->boxes[i].draw(this->window);
    }

    for (int i = 0; i < locks.size(); i++) {
        this->locks[i].draw(this->window);
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
        thread t(&CustomLock::fadeOut, &this->locks[0]);
        t.detach();
        if (this->plr.playerTile.x - 1 >= 0) {
            if (this->level[this->plr.playerTile.y][this->plr.playerTile.x - 1] == 2) {
                for (int i = 0; i < attachedBoxes.size(); i++) {
                    if (this->attachedBoxes[i]->position.x - 1 >= 0) {
                        if (this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x - 1] == 2) {
                            this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x] = 2;
                                
                            canMove = true;
                        }
                        else {
                            canMove = false;
                            break;

                        }
                    }
                }
                if (canMove) {
                    animatePlayerMovement(-80, 0);
                }
            }
        }
    }
    else if (this->event.key.code == Keyboard::D) {
        if (this->plr.playerTile.x + 1 <= 15) {
            if (this->level[this->plr.playerTile.y][this->plr.playerTile.x + 1] == 2) {
                for (int i = 0; i < attachedBoxes.size(); i++) {
                    if (this->attachedBoxes[i]->position.x + 1 <= 15) {
                        if (this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x + 1] == 2) {
                            this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x] = 2;
                                
                            canMove = true;

                        }
                        else {
                            canMove = false;
                            break;
                        }
                    }
                }
                if (canMove) {
                    animatePlayerMovement(80, 0);
                }
            }
        }
    }
    else if (this->event.key.code == Keyboard::S) {
        if (this->plr.playerTile.y + 1 <= 8) {
            if (this->level[this->plr.playerTile.y + 1][this->plr.playerTile.x] == 2) {
                for (int i = 0; i < attachedBoxes.size(); i++) {
                    if (this->attachedBoxes[i]->position.y + 1 <= 8) {
                        if (this->level[this->attachedBoxes[i]->position.y + 1][this->attachedBoxes[i]->position.x] == 2) {
                            this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x] = 2;

                            canMove = true;
                        }
                        else {
                            canMove = false;
                            break;

                        }
                    }
                }

                if (canMove) {
                    animatePlayerMovement(0, 80);
                }
            }
        }
    }
    else if (this->event.key.code == Keyboard::W) {

        if (this->plr.playerTile.y - 1 >= 0) {
            if (this->level[this->plr.playerTile.y - 1][this->plr.playerTile.x] == 2) {
                for (int i = 0; i < attachedBoxes.size(); i++) {
                    if (this->attachedBoxes[i]->position.y - 1 >= 0) {
                        if (this->level[this->attachedBoxes[i]->position.y - 1][this->attachedBoxes[i]->position.x] == 2) {
                            this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x] = 2;

                            canMove = true;
                        }
                        else {
                            canMove = false;
                            break;
                        }
                    }
                }

                if (canMove) {
                    animatePlayerMovement(0, -80);
                }
            }
        }
    }

    checkForAdjacentBoxes();

    //checkForUnlock();
}

void game::animatePlayerMovement(int xChange, int yChange) {
    if (xChange < 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            this->plr.move(Vector2f(-16, 0));
            for (int i = 0; i < attachedBoxes.size(); i++) {
                this->attachedBoxes[i]->move(Vector2f(-16, 0));
            }
        }
    }
    else if (xChange > 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            this->plr.move(Vector2f(16, 0));
            for (int i = 0; i < attachedBoxes.size(); i++) {
                this->attachedBoxes[i]->move(Vector2f(16, 0));
            }
        }
    }
    if (yChange < 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            this->plr.move(Vector2f(0, -16));
            for (int i = 0; i < attachedBoxes.size(); i++) {
                this->attachedBoxes[i]->move(Vector2f(0, -16));
            }
        }
    }
    else if (yChange > 0) {
        for (int i = 0; i < 5; i++) {
            drawWindow();
            this->plr.move(Vector2f(0, 16));
            for (int i = 0; i < attachedBoxes.size(); i++) {
                this->attachedBoxes[i]->move(Vector2f(0, 16));
            }
        }
    }
}

void game::checkForAdjacentBoxes() {
    if (this->plr.playerTile.y - 1 >= 0) {
        for (int i = 0; i < boxes.size(); i++) {
            if (this->level[this->plr.playerTile.y - 1][this->plr.playerTile.x] == 6 && (this->plr.playerTile.y - 1 == boxes[i].position.y && this->plr.playerTile.x == boxes[i].position.x)) {
                attachedBoxes.push_back(&boxes[i]);
            }
        }
    }

    if (this->plr.playerTile.y + 1 <= 8) {
        for (int i = 0; i < boxes.size(); i++) {
            if (this->level[this->plr.playerTile.y + 1][this->plr.playerTile.x] == 6 && (this->plr.playerTile.y + 1 == boxes[i].position.y && this->plr.playerTile.x == boxes[i].position.x)) {
                attachedBoxes.push_back(&this->boxes[i]);
            }
        }
    }

    if (this->plr.playerTile.x - 1 >= 0) {
        for (int i = 0; i < boxes.size(); i++) {
            if (this->level[this->plr.playerTile.y][this->plr.playerTile.x - 1] == 6 && (this->plr.playerTile.y == boxes[i].position.y && this->plr.playerTile.x - 1 == boxes[i].position.x)) {
                attachedBoxes.push_back(&this->boxes[i]);
            }
        }
    }

    if (this->plr.playerTile.y + 1 <= 15) {
        for (int i = 0; i < boxes.size(); i++) {
            if (this->level[this->plr.playerTile.y][this->plr.playerTile.x + 1] == 6 && (this->plr.playerTile.y == boxes[i].position.y && this->plr.playerTile.x + 1 == boxes[i].position.x)) {
                attachedBoxes.push_back(&this->boxes[i]);
            }
        }
    }
}