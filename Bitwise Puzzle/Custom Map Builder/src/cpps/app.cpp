#include "app.hpp"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

void App::initWindow() {
	voidTexture.loadFromFile("./Assets/Void.png");
	wallTexture.loadFromFile("./Assets/wall.png");
	floorTexture.loadFromFile("./Assets/Floor.png");

	textureMap = {
		{0, this->voidTexture},
		{1, this->wallTexture},
		{2, this->floorTexture},
	};

	json _json;

	std::fstream file("./Maps/custom.json");

	map = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	for (int i = 0; i < 9; i++) {
		this->tiles.push_back(std::vector<Sprite>());
		for (int j = 0; j < 16; j++) {
			Sprite sprite;

			sprite.setTexture(textureMap[this->map[i][j]]);
			sprite.setPosition(j * 80, i * 80);
			this->tiles[i].push_back(sprite);
		}
	}

	this->window.create(VideoMode(1280, 720), "Custom Map Builder");
	updateWindow();
}

void App::updateWindow() {
	while (this->window.isOpen()) {
		while (this->window.pollEvent(this->event)) {
			if (event.type == Event::Closed) {
				this->window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				handleInput();
			}
		}

		renderWindow();
	}
}

void App::renderWindow() {
	this->window.clear();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 16; j++) {
			this->window.draw(tiles[i][j]);
		}
	}

	this->window.display();
}

void App::handleInput() {
	if (this->event.mouseButton.button == 0) {
		float x = event.mouseButton.x;
		float y = event.mouseButton.y;

		int tileX = x / 80;
		int tileY = y / 80;

		std::cout << tileX << " " << tileY << std::endl;

		this->map[tileY][tileX] = 2;
		this->tiles[tileY][tileX].setTexture(textureMap[map[tileY][tileX]]);
	}
}




/* _json["2"] = json::array();

for (int i = 0; i < 9; i++) {
	int row[16] = {};
	for (int j = 0; j < 16; j++) {
		row[j] = map[i][j];
	}

	_json["2"].push_back(row);
}

file << _json.dump(4, ' '); */