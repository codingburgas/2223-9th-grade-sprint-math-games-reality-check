#include "app.hpp"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

void App::initWindow() {
	this->voidTexture.loadFromFile("./Assets/Void.png");
	this->wallTexture.loadFromFile("./Assets/wall.png");
	this->floorTexture.loadFromFile("./Assets/Floor.png");
	this->flagTexture.loadFromFile("./Assets/FlagSingle.png");
	this->box0Texture.loadFromFile("./Assets/Box0.png");
	this->box1Texture.loadFromFile("./Assets/Box1.png");
	this->lock0Texture.loadFromFile("./Assets/Lock0.png");
	this->lock1Texture.loadFromFile("./Assets/Lock1.png");
	this->spawnTexture.loadFromFile("./Assets/PlayerSpawn.png");
	this->ANDTexture.loadFromFile("./Assets/ANDoperator.png");
	this->ORTexture.loadFromFile("./Assets/ORoperator.png");
	this->XORTexture.loadFromFile("./Assets/XORoperator.png");

	textureMap = {
		{0, this->voidTexture},
		{1, this->wallTexture},
		{2, this->floorTexture},
		{3, this->flagTexture},
		{4, this->lock0Texture},
		{5, this->lock1Texture},
		{6, this->box0Texture},
		{7, this->box1Texture},
		{8, this->spawnTexture}
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

	this->characterSelector.setSize(Vector2f(80, 80));
	this->characterSelector.setOutlineThickness(-3);
	this->characterSelector.setFillColor(Color::Transparent);
	this->characterSelector.setOutlineColor(Color::White);
	this->characterSelector.setPosition(1430, 320);

	this->selectorVoid.setTexture(this->voidTexture);
	this->selectorWall.setTexture(this->wallTexture);
	this->selectorFloor.setTexture(this->floorTexture);
	this->selectorFlag.setTexture(this->flagTexture);
	this->selectorBox0.setTexture(this->box0Texture);
	this->selectorBox1.setTexture(this->box1Texture);
	this->selectorLock0.setTexture(this->lock0Texture);
	this->selectorLock1.setTexture(this->lock1Texture);
	this->selectorSpawn.setTexture(this->spawnTexture);
	this->ANDSprite.setTexture(this->ANDTexture);
	this->ORSprite.setTexture(this->ORTexture);
	this->XORSprite.setTexture(this->XORTexture);

	this->selectorVoid.setPosition(1330, 20);
	this->selectorWall.setPosition(1330, 120);
	this->selectorFloor.setPosition(1330, 220);
	this->selectorFlag.setPosition(Vector2f(1330, 320));
	this->selectorBox0.setPosition(Vector2f(1330, 420));
	this->selectorBox1.setPosition(Vector2f(1330, 520));
	this->selectorLock0.setPosition(Vector2f(1430, 20));
	this->selectorLock1.setPosition(Vector2f(1430, 120));
	this->selectorSpawn.setPosition(Vector2f(1430, 220));
	this->ANDSprite.setPosition(Vector2f(1430, 320));
	this->ORSprite.setPosition(Vector2f(1430, 420));
	this->XORSprite.setPosition(Vector2f(1430, 520));

	this->saveButton.setPosition(1350, 630);
	this->saveButton.setSize(Vector2f(140, 60));
	this->saveButton.setOutlineThickness(2);
	this->saveButton.setOutlineColor(Color::White);
	this->saveButton.setFillColor(Color(54, 201, 115));

	this->currentTile = 0;
	this->currentCharacter = 0;

	this->window.create(VideoMode(1560, 720), "Custom Map Builder");
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
	this->window.draw(this->selectorFlag);
	this->window.draw(this->selectorBox0);
	this->window.draw(this->selectorBox1);
	this->window.draw(this->selectorLock0);
	this->window.draw(this->selectorLock1);
	this->window.draw(this->selectorSpawn);
	this->window.draw(this->ANDSprite);
	this->window.draw(this->ORSprite);
	this->window.draw(this->XORSprite);
	this->window.draw(this->characterSelector);

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

			Vector2f flagStartPos(this->selectorFlag.getPosition().x, this->selectorFlag.getPosition().y);
			Vector2f flagEndPos(this->selectorFlag.getPosition().x + 80, this->selectorFlag.getPosition().y + 80);

			Vector2f box0StartPos(this->selectorBox0.getPosition().x, this->selectorBox0.getPosition().y);
			Vector2f box0EndPos(this->selectorBox0.getPosition().x + 80, this->selectorBox0.getPosition().y + 80);

			Vector2f box1StartPos(this->selectorBox1.getPosition().x, this->selectorBox1.getPosition().y);
			Vector2f box1EndPos(this->selectorBox1.getPosition().x + 80, this->selectorBox1.getPosition().y + 80);

			Vector2f lock0StartPos(this->selectorLock0.getPosition().x, this->selectorLock0.getPosition().y);
			Vector2f lock0EndPos(this->selectorLock0.getPosition().x + 80, this->selectorLock0.getPosition().y + 80);

			Vector2f lock1StartPos(this->selectorLock1.getPosition().x, this->selectorLock1.getPosition().y);
			Vector2f lock1EndPos(this->selectorLock1.getPosition().x + 80, this->selectorLock1.getPosition().y + 80);

			Vector2f spawnStartPos(this->selectorSpawn.getPosition().x, this->selectorSpawn.getPosition().y);
			Vector2f spawnEndPos(this->selectorSpawn.getPosition().x + 80, this->selectorSpawn.getPosition().y + 80);

			Vector2f buttonStartPos(this->saveButton.getPosition().x, this->saveButton.getPosition().y);
			Vector2f buttonEndPos(this->saveButton.getPosition().x + 140, this->saveButton.getPosition().y + 60);

			Vector2f ANDStartPos(this->ANDSprite.getPosition().x, this->ANDSprite.getPosition().y);
			Vector2f ANDEndPos(this->ANDSprite.getPosition().x + 80, this->ANDSprite.getPosition().y + 80);

			Vector2f ORStartPos(this->ORSprite.getPosition().x, this->ORSprite.getPosition().y);
			Vector2f OREndPos(this->ORSprite.getPosition().x + 80, this->ORSprite.getPosition().y + 80);

			Vector2f XORStartPos(this->XORSprite.getPosition().x, this->XORSprite.getPosition().y);
			Vector2f XOREndPos(this->XORSprite.getPosition().x + 140, this->XORSprite.getPosition().y + 60);


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
			else if (x >= flagStartPos.x && x <= flagEndPos.x && y >= flagStartPos.y && y <= flagEndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1330, 320));
				this->currentTile = 3;
			}
			else if (x >= lock0StartPos.x && x <= lock0EndPos.x && y >= lock0StartPos.y && y <= lock0EndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1430, 20));
				this->currentTile = 4;
			}
			else if (x >= lock1StartPos.x && x <= lock1EndPos.x && y >= lock1StartPos.y && y <= lock1EndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1430, 120));
				this->currentTile = 5;
			}
			else if (x >= box0StartPos.x && x <= box0EndPos.x && y >= box0StartPos.y && y <= box0EndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1330, 420));
				this->currentTile = 6;
			}
			else if (x >= box1StartPos.x && x <= box1EndPos.x && y >= box1StartPos.y && y <= box1EndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1330, 520));
				this->currentTile = 7;
			}
			else if (x >= spawnStartPos.x && x <= spawnEndPos.x && y >= spawnStartPos.y && y <= spawnEndPos.y) {
				this->selectorBorder.setPosition(Vector2f(1430, 220));
				this->currentTile = 8;
			}

			else if (x >= ANDStartPos.x && x <= ANDEndPos.x && y >= ANDStartPos.y && y <= ANDEndPos.y) {
				this->characterSelector.setPosition(Vector2f(1430, 320));
				this->currentCharacter = 0;
			}
			else if (x >= ORStartPos.x && x <= OREndPos.x && y >= ORStartPos.y && y <= OREndPos.y) {
				this->characterSelector.setPosition(Vector2f(1430, 420));
				this->currentCharacter = 1;
			}
			else if (x >= XORStartPos.x && x <= XOREndPos.x && y >= XORStartPos.y && y <= XOREndPos.y) {
				this->characterSelector.setPosition(Vector2f(1430, 520));
				this->currentCharacter = 2;
			}

			else if (x >= buttonStartPos.x && x <= buttonEndPos.x && y >= buttonStartPos.y && y <= buttonEndPos.y) {
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

	std::string lvl = _json.dump();
	std::string temp = "";

	for (int i = 0; i < lvl.size(); i++) {
		if (lvl[i] == ',' && i >= 43 && i <= lvl.size() - 35 && lvl[i - 1] == ']') {
			temp += ", \n        ";
		}
		else {
			temp += lvl[i];
		}

		if (i == 315) {
			temp += ",\n        [" + std::to_string(this->currentCharacter) + "]\n    ";
		}
		else if (i == 316) {
			temp += "\n";
		}
		else if (i == 0) {
			temp += "\n    ";
		}
		else if (i == 9) {
			temp += "\n    ";
		}
		else if (i == 10) {
			temp += "\n        ";
		}
	}

	file.clear();
	file << temp;
	file.close();
}