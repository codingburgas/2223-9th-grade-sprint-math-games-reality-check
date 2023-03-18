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

	this->selectorBorder.setSize(Vector2f(80,80));
	this->selectorBorder.setOutlineThickness(-3);
	this->selectorBorder.setFillColor(Color::Transparent);
	this->selectorBorder.setOutlineColor(Color::White);
	this->selectorBorder.setPosition(1330, 20);

	this->selectorVoid.setTexture(this->voidTexture);
	this->selectorWall.setTexture(this->wallTexture);
	this->selectorFloor.setTexture(this->floorTexture);

	this->selectorVoid.setPosition(1330, 20);
	this->selectorWall.setPosition(1330, 120);
	this->selectorFloor.setPosition(1330, 220);

	this->saveButton.setPosition(1300, 630);
	this->saveButton.setSize(Vector2f(140, 60));
	this->saveButton.setOutlineThickness(2);
	this->saveButton.setOutlineColor(Color::White);
	this->saveButton.setFillColor(Color(54, 201, 115));


	this->currentTile = 0;

	this->window.create(VideoMode(1460, 720), "Custom Map Builder");
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
	this->window.clear(Color(60,60,60));

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 16; j++) {
			this->window.draw(tiles[i][j]);
		}
	}

	this->window.draw(this->selectorVoid);
	this->window.draw(this->selectorWall);
	this->window.draw(this->selectorFloor);

	this->window.draw(this->selectorBorder);

	this->window.draw(this->saveButton);

	this->window.display();
}

void App::handleInput() {
	if (this->event.mouseButton.button == 0) {
		float x = event.mouseButton.x;
		float y = event.mouseButton.y;

		if (x < 1280) {
			int tileX = x / 80;
			int tileY = y / 80;

			this->map[tileY][tileX] = this->currentTile;
			this->tiles[tileY][tileX].setTexture(textureMap[map[tileY][tileX]]);
		}
		else {
			Vector2f voidStartPos(this->selectorVoid.getPosition().x, this->selectorVoid.getPosition().y);
			Vector2f voidEndPos(this->selectorVoid.getPosition().x + 80, this->selectorVoid.getPosition().y + 80);

			Vector2f wallStartPos(this->selectorWall.getPosition().x, this->selectorWall.getPosition().y);
			Vector2f wallEndPos(this->selectorWall.getPosition().x + 80, this->selectorWall.getPosition().y + 80);

			Vector2f floorStartPos(this->selectorFloor.getPosition().x, this->selectorFloor.getPosition().y);
			Vector2f floorEndPos(this->selectorFloor.getPosition().x + 80, this->selectorFloor.getPosition().y + 80);

			Vector2f buttonStartPos(this->saveButton.getPosition().x, this->saveButton.getPosition().y);
			Vector2f buttonEndPos(this->saveButton.getPosition().x + 140, this->saveButton.getPosition().y + 60);

			if (x >= voidStartPos.x && x <= voidEndPos.x && y >= voidStartPos.y && y <= voidEndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1330, 20));
				this->currentTile = 0;
			}
			else if (x >= wallStartPos.x && x <= wallEndPos.x && y >= wallStartPos.y && y <= wallEndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1330, 120));
				this->currentTile = 1;

			}
			else if (x >= floorStartPos.x && x <= floorEndPos.x && y >= floorStartPos.y && y <= floorEndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1330, 220));
				this->currentTile = 2;
			}
			else if (x >= buttonStartPos.x && x <= buttonEndPos.x && y >= buttonStartPos.y && y <= buttonEndPos.y) {
				std::cout << "s";
				saveLevel();
			}
		}
	}
}

void App::saveLevel() {
	json _json;

	std::fstream file("./Maps/custom.json");
	_json["custom"] = json::array();

	for (int i = 0; i < 9; i++) {
		int row[16] = {};
		for (int j = 0; j < 16; j++) {
			row[j] = map[i][j];
		}

		_json["custom"].push_back(row);
	}

	file << _json.dump(4, ' ');
	file.close();
}