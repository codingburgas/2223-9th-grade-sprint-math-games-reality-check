#include "game.h"
#include <map>
#include "json.hpp"
#include <fstream>
#include <thread>
#include <future>

using json = nlohmann::json;

game::game(Vector2u size, string title) {
    this->window.create(VideoMode(size.x, size.y), title);
	this->window.setFramerateLimit(60);
    this->window.setKeyRepeatEnabled(false);

    this->voidTexture.loadFromFile("./Assets/void.png");
    this->wallTexture.loadFromFile("./Assets/wall.png");
    this->floorTexture.loadFromFile("./Assets/floor.png");
    this->flagTexture.loadFromFile("./Assets/Flag.png");
    this->box0Texture.loadFromFile("./Assets/Box0.png");
    this->box1Texture.loadFromFile("./Assets/Box1.png");
    this->lock0Texture.loadFromFile("./Assets/Lock0.png");
    this->lock1Texture.loadFromFile("./Assets/Lock1.png");
    this->plrTexture.loadFromFile("./Assets/ANDoperator.png");
    this->ANDTexture.loadFromFile("./Assets/ANDoperator.png");
    this->ORTexture.loadFromFile("./Assets/ORoperator.png");
    this->XORTexture.loadFromFile("./Assets/XORoperator.png");
    
    // 0 - void
    // 1 - stena
    // 2 - pod
    // 3 - flagche
    // 4 - klyuchalka 0
    // 5 - klyuchalka 1
    // 6 - kutiya 0
    // 7 - kutiya 1

    this->textureMap = {
        {0, this->voidTexture},
        {1, this->wallTexture},
        {2, this->floorTexture},
        {4, this->lock0Texture},
        {5, this->lock1Texture},
        {6, this->box0Texture},
        {7, this->box1Texture}
    };

    this->plrTextures = {
        {0, this->ANDTexture},
        {1, this->ORTexture},
        {2, this->XORTexture}
    };

    this->currentLevel = 2;
    loadLevel(to_string(this->currentLevel));
    this->plr.setTexture(plrTexture);

    this->canMove = true;
    this->flag.setProperties(flagTexture, 11, 0.09);
    MainMenu mainMenu(Vector2f(0,0), window);
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
            else if (this->level[i][j] == 3) {
                this->flag.setPosition(Vector2f(j * 80.f, i * 80.f));
                
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
                if (this->level[i][j] == 4) {
                    lock.setValue(0);
                }
                else {
                    lock.setValue(1);
                }

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

                if (this->level[i][j] == 6) {
                    box.setValue(0);
                }
                else {
                    box.setValue(1);
                }

                this->boxes.push_back(box);
            }
            else if (this->level[i][j] == 8) {
                Tile tile;
                tile.setTexture(textureMap[2]);
                tile.setPosition(Vector2f(j * 80.f, i * 80.f));

                this->tiles[i].push_back(tile);

                this->plr.setPosition(Vector2f(j * 80.f, i * 80.f));
                this->level[i][j] = 2;
            }
        }
    }
    this->plrTexture.update(this->plrTextures[this->level[9][0]]);


}

void game::drawWindow()
{
    this->window.clear();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 16; j++) {
            this->tiles[i][j].draw(this->window);
        }
    }
    
    this->flag.update(this->dt);
    this->flag.draw(window);
    
    for (int i = 0; i < boxes.size(); i++) {
        this->boxes[i].draw(this->window);
    }

    this->plr.draw(this->window);

    for (int i = 0; i < locks.size(); i++) {
        if (this->locks[i].drawable) {
            this->locks[i].draw(this->window);
        }
    }


    this->window.display();

    this->dt = clock.restart();
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
            if (this->level[this->plr.playerTile.y][this->plr.playerTile.x - 1] == 2 || this->level[this->plr.playerTile.y][this->plr.playerTile.x - 1] == 3) {
                for (int i = 0; i < attachedBoxes.size(); i++) {
                    if (this->attachedBoxes[i]->position.x - 1 >= 0) {
                        if (this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x - 1] == 2 || this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x - 1] == 3) {
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
            if (this->level[this->plr.playerTile.y][this->plr.playerTile.x + 1] == 2 || this->level[this->plr.playerTile.y][this->plr.playerTile.x + 1] == 3) {
                for (int i = 0; i < attachedBoxes.size(); i++) {
                    if (this->attachedBoxes[i]->position.x + 1 <= 15) {
                        if (this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x + 1] == 2 || this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x + 1] == 3) {
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
            if (this->level[this->plr.playerTile.y + 1][this->plr.playerTile.x] == 2 || this->level[this->plr.playerTile.y + 1][this->plr.playerTile.x] == 3) {
                for (int i = 0; i < attachedBoxes.size(); i++) {
                    if (this->attachedBoxes[i]->position.y + 1 <= 8) {
                        if (this->level[this->attachedBoxes[i]->position.y + 1][this->attachedBoxes[i]->position.x] == 2 || this->level[this->attachedBoxes[i]->position.y + 1][this->attachedBoxes[i]->position.x] == 3) {
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
            if (this->level[this->plr.playerTile.y - 1][this->plr.playerTile.x] == 2 || this->level[this->plr.playerTile.y - 1][this->plr.playerTile.x] == 3) {
                for (int i = 0; i < attachedBoxes.size(); i++) {
                    if (this->attachedBoxes[i]->position.y - 1 >= 0) {
                        if (this->level[this->attachedBoxes[i]->position.y - 1][this->attachedBoxes[i]->position.x] == 2 || this->level[this->attachedBoxes[i]->position.y - 1][this->attachedBoxes[i]->position.x] == 3) {
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
    else if (this->event.key.code == Keyboard::E) {
        rotateE();
    }
    else if (this->event.key.code == Keyboard::Q) {
        rotateQ();
    }

    if (this->level[this->plr.playerTile.y][this->plr.playerTile.x] == 3) {
        this->level.clear();
        this->boxes.clear();
        this->locks.clear();
        this->tiles.clear();
        this->attachedBoxes.clear();
        currentLevel++;
        return loadLevel(to_string(currentLevel));
    }
    else {
        for (int i = 0; i < attachedBoxes.size(); i++) {
            if (this->attachedBoxes[i]->position == this->flag.position) {
                this->level.clear();
                this->boxes.clear();
                this->locks.clear();
                this->tiles.clear();
                this->attachedBoxes.clear();
                currentLevel++;
                return loadLevel(to_string(currentLevel));
                break;
            }
        }

    }

    checkForAdjacentBoxes();
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
    bool attachedNewBox = false;
    if (this->plr.playerTile.y - 1 >= 0) {
        for (int i = 0; i < boxes.size(); i++) {
            if (this->level[this->plr.playerTile.y - 1][this->plr.playerTile.x] >= 6 && (this->plr.playerTile.y - 1 == boxes[i].position.y && this->plr.playerTile.x == boxes[i].position.x)) {
                this->level[this->plr.playerTile.y - 1][this->plr.playerTile.x] = 2;

                attachedBoxes.push_back(&boxes[i]);
                attachedNewBox = true;

            }
        }
    }

    if (this->plr.playerTile.y + 1 <= 8) {
        for (int i = 0; i < boxes.size(); i++) {
            if (this->level[this->plr.playerTile.y + 1][this->plr.playerTile.x] >= 6 && (this->plr.playerTile.y + 1 == boxes[i].position.y && this->plr.playerTile.x == boxes[i].position.x)) {
                this->level[this->plr.playerTile.y + 1][this->plr.playerTile.x] = 2;

                attachedBoxes.push_back(&this->boxes[i]);
                attachedNewBox = true;
            }
        }
    }

    if (this->plr.playerTile.x - 1 >= 0) {
        for (int i = 0; i < boxes.size(); i++) {
            if (this->level[this->plr.playerTile.y][this->plr.playerTile.x - 1] >= 6 && (this->plr.playerTile.y == boxes[i].position.y && this->plr.playerTile.x - 1 == boxes[i].position.x)) {
                this->level[this->plr.playerTile.y][this->plr.playerTile.x - 1] = 2;

                attachedBoxes.push_back(&this->boxes[i]);
                attachedNewBox = true;
            }
        }
    }

    if (this->plr.playerTile.y + 1 <= 15) {
        for (int i = 0; i < boxes.size(); i++) {
            if (this->level[this->plr.playerTile.y][this->plr.playerTile.x + 1] >= 6 && (this->plr.playerTile.y == boxes[i].position.y && this->plr.playerTile.x + 1 == boxes[i].position.x)) {
                this->level[this->plr.playerTile.y][this->plr.playerTile.x + 1] = 2;

                attachedBoxes.push_back(&this->boxes[i]);
                attachedNewBox = true;
            }
        }
    }

    if (attachedNewBox && this->attachedBoxes.size() > 1) {
        sort(this->attachedBoxes.begin(), this->attachedBoxes.end(), [](const Box* box1, const Box* box2) {
            return (box1->value > box2->value);
            });
        checkForUnlock();
    }

    attachedNewBox = false;
}

void game::checkForUnlock() {
    for (int i = 0; i < this->locks.size(); i++) {
        for (int j = 0; j < this->attachedBoxes.size(); j += 2) {
            if (j + 1 < this->attachedBoxes.size()) {
                if (this->attachedBoxes[j]->position.y != this->plr.playerTile.y && this->attachedBoxes[j + 1]->position.y != this->plr.playerTile.y) {
                    if (this->locks[i].value == (this->attachedBoxes[j]->value || this->attachedBoxes[j + 1]->value)) {
                        this->level[this->locks[i].position.y][this->locks[i].position.x] = 2;
                        thread t(&CustomLock::fadeOut, &this->locks[i]);
                        t.detach();
                        break;
                    }
                }
                else if (this->attachedBoxes[j]->position.x != this->plr.playerTile.x && this->attachedBoxes[j + 1]->position.x != this->plr.playerTile.x) {
                    if (this->locks[i].value == (this->attachedBoxes[j]->value || this->attachedBoxes[j + 1]->value)) {
                        this->level[this->locks[i].position.y][this->locks[i].position.x] = 2;
                        thread t(&CustomLock::fadeOut, &this->locks[i]);
                        t.detach();
                        break;
                    }
                }
            }
        }
    }
}


void game::animateBoxRotation(char key) {
    // 0 - starts from left side
    // 1 - starts from top side
    // 2 - starts from right side
    // 3 - starts from bottom

    vector<int> pos;

    for (int i = 0; i < this->positions.size(); i++) {
        pos.push_back(int());
        if (this->attachedBoxes[i]->position.y == this->plr.playerTile.y) {
            for (int j = 0; j < 4; j++) {
                drawWindow();
                if (key == 'e') {
                    this->attachedBoxes[i]->move(Vector2f(0, this->positions[i].y / 4));
                    pos[i] = 0;
                }
                else {
                    this->attachedBoxes[i]->move(Vector2f(0, -this->positions[i].y / 4));
                    pos[i] = 2;
                }
            }
        }
        else {
            for (int j = 0; j < 4; j++) {
                drawWindow();
                if (key == 'e') {
                    this->attachedBoxes[i]->move(Vector2f(this->positions[i].x / 4, 0));
                    pos[i] = 1;
                }
                else {
                    this->attachedBoxes[i]->move(Vector2f(-this->positions[i].x / 4, 0));
                    pos[i] = 3;
                }
            }
        }
    }

    for (int i = 0; i < this->positions.size(); i++) {
        if (pos[i] == 1 || pos[i] == 3) {
            for (int j = 0; j < 4; j++) {
                drawWindow();
                if (key == 'e') {
                    this->attachedBoxes[i]->move(Vector2f(0, this->positions[i].y / 4));
                }
                else {
                    this->attachedBoxes[i]->move(Vector2f(0, -this->positions[i].y / 4));
                }
            }
        }
        else {
            for (int j = 0; j < 4; j++) {
                drawWindow();
                if (key == 'e') {
                    this->attachedBoxes[i]->move(Vector2f(this->positions[i].x / 4, 0));
                }
                else {
                    this->attachedBoxes[i]->move(Vector2f(-this->positions[i].x / 4, 0));
                }
            }
        }
    }
}


void game::rotateE() {
    bool broke = false;

    for (int i = 0; i < this->attachedBoxes.size(); i++) {
        if (this->attachedBoxes[i]->position.y != this->plr.playerTile.y) {
            if (this->attachedBoxes[i]->position.y < this->plr.playerTile.y) {
                if (this->attachedBoxes[i]->position.x + 1 <= 15) {
                    if (this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x + 1] == 2 && this->level[this->attachedBoxes[i]->position.y + 1][this->attachedBoxes[i]->position.x + 1] == 2) {
                        this->positions.push_back(Vector2f((this->attachedBoxes[i]->position.x + 1) * 80 - this->attachedBoxes[i]->position.x * 80.f, (this->attachedBoxes[i]->position.y + 1) * 80 - this->attachedBoxes[i]->position.y * 80.f));
                    }
                    else {
                        broke = true;
                        break;
                    }
                }
            }
            else {
                if (this->attachedBoxes[i]->position.x - 1 >= 0) {
                    if (this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x - 1] == 2 && this->level[this->attachedBoxes[i]->position.y - 1][this->attachedBoxes[i]->position.x - 1] == 2) {
                        this->positions.push_back(Vector2f((this->attachedBoxes[i]->position.x - 1) * 80 - this->attachedBoxes[i]->position.x * 80.f, (this->attachedBoxes[i]->position.y - 1) * 80 - this->attachedBoxes[i]->position.y * 80.f));
                    }
                    else {
                        broke = true;
                        break;
                    }
                }
            }
        }
        else {
            if (this->attachedBoxes[i]->position.x < this->plr.playerTile.x) {
                if (this->attachedBoxes[i]->position.y - 1 >= 0) {
                    if (this->level[this->attachedBoxes[i]->position.y - 1][this->attachedBoxes[i]->position.x] == 2 && this->level[this->attachedBoxes[i]->position.y - 1][this->attachedBoxes[i]->position.x + 1] == 2) {
                        this->positions.push_back(Vector2f((this->attachedBoxes[i]->position.x + 1) * 80 - this->attachedBoxes[i]->position.x * 80.f, (this->attachedBoxes[i]->position.y - 1) * 80 - this->attachedBoxes[i]->position.y * 80.f));
                    }
                    else {
                        broke = true;
                        break;
                    }
                }
            }
            else {
                if (this->attachedBoxes[i]->position.y + 1 <= 15) {
                    if (this->level[this->attachedBoxes[i]->position.y + 1][this->attachedBoxes[i]->position.x] == 2 && this->level[this->attachedBoxes[i]->position.y + 1][this->attachedBoxes[i]->position.x - 1] == 2) {
                        this->positions.push_back(Vector2f((this->attachedBoxes[i]->position.x - 1) * 80 - this->attachedBoxes[i]->position.x * 80.f, (this->attachedBoxes[i]->position.y + 1) * 80 - this->attachedBoxes[i]->position.y * 80.f));
                    }
                    else {
                        broke = true;
                        break;
                    }
                }
            }
        }
    }

    if (!broke) {
        animateBoxRotation('e');
    }
    this->positions.clear();
}

void game::rotateQ() {
    bool broke = false;

    for (int i = 0; i < this->attachedBoxes.size(); i++) {
        if (this->attachedBoxes[i]->position.y != this->plr.playerTile.y) {
            if (this->attachedBoxes[i]->position.y < this->plr.playerTile.y) {
                if (this->attachedBoxes[i]->position.x - 1 >= 0) {
                    if (this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x - 1] == 2 && this->level[this->attachedBoxes[i]->position.y + 1][this->attachedBoxes[i]->position.x - 1] == 2) {
                        this->positions.push_back(Vector2f(-((this->attachedBoxes[i]->position.x - 1) * 80 - this->attachedBoxes[i]->position.x * 80.f), -((this->attachedBoxes[i]->position.y + 1) * 80 - this->attachedBoxes[i]->position.y * 80.f)));
                    }
                    else {
                        broke = true;
                        break;
                    }
                }
            }
            else {
                if (this->attachedBoxes[i]->position.x + 1 <= 15) {
                    if (this->level[this->attachedBoxes[i]->position.y][this->attachedBoxes[i]->position.x + 1] == 2 && this->level[this->attachedBoxes[i]->position.y - 1][this->attachedBoxes[i]->position.x + 1] == 2) {
                        this->positions.push_back(Vector2f(-((this->attachedBoxes[i]->position.x + 1) * 80 - this->attachedBoxes[i]->position.x * 80.f), -((this->attachedBoxes[i]->position.y - 1) * 80 - this->attachedBoxes[i]->position.y * 80.f)));
                    }
                    else {
                        broke = true;
                        break;
                    }
                }
            }
        }
        else {
            if (this->attachedBoxes[i]->position.x < this->plr.playerTile.x) {
                if (this->attachedBoxes[i]->position.y + 1 <= 15) {
                    if (this->level[this->attachedBoxes[i]->position.y + 1][this->attachedBoxes[i]->position.x] == 2 && this->level[this->attachedBoxes[i]->position.y + 1][this->attachedBoxes[i]->position.x + 1] == 2) {
                        this->positions.push_back(Vector2f(-((this->attachedBoxes[i]->position.x + 1) * 80 - this->attachedBoxes[i]->position.x * 80.f), -((this->attachedBoxes[i]->position.y + 1) * 80 - this->attachedBoxes[i]->position.y * 80.f)));
                    }
                    else {
                        broke = true;
                        break;
                    }
                }
            }
            else {
                if (this->attachedBoxes[i]->position.y - 1 >= 0) {
                    if (this->level[this->attachedBoxes[i]->position.y - 1][this->attachedBoxes[i]->position.x] == 2 && this->level[this->attachedBoxes[i]->position.y - 1][this->attachedBoxes[i]->position.x - 1] == 2) {
                        this->positions.push_back(Vector2f(-((this->attachedBoxes[i]->position.x - 1) * 80 - this->attachedBoxes[i]->position.x * 80.f), -((this->attachedBoxes[i]->position.y - 1) * 80 - this->attachedBoxes[i]->position.y * 80.f)));
                    }
                    else {
                        broke = true;
                        break;
                    }
                }
            }
        }
    }

    if (!broke) {
        animateBoxRotation('q');
    }
    this->positions.clear();
}