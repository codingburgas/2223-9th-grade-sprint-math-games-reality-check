#include "precompile.hpp"
#include <string>

class App {
public:
	void initWindow();
	void updateWindow();
	void renderWindow();
	void handleInput();
	void saveLevel();
private:
	int currentTile;
	int currentCharacter;
	RenderWindow window;
	Event event;
	Texture voidTexture;
	Texture wallTexture;
	Texture floorTexture;
	Texture flagTexture;
	Texture lock0Texture;
	Texture lock1Texture;
	Texture box0Texture;
	Texture box1Texture;
	Texture spawnTexture;
	Texture ANDTexture;
	Texture ORTexture;
	Texture XORTexture;
	Sprite selectorVoid;
	Sprite selectorWall;
	Sprite selectorFloor;
	Sprite selectorFlag;
	Sprite selectorBox0;
	Sprite selectorBox1;
	Sprite selectorLock0;
	Sprite selectorLock1;
	Sprite selectorSpawn;
	Sprite ANDSprite;
	Sprite ORSprite;
	Sprite XORSprite;
	RectangleShape selectorBorder;
	RectangleShape characterSelector;
	RectangleShape saveButton;
	std::map<int, Texture> textureMap;
	std::vector<std::vector<int>> map;
	std::vector<std::vector<Sprite>> tiles;
};