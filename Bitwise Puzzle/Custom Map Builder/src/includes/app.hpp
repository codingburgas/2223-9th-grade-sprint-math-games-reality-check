#include "precompile.hpp"

class App {
public:
	void initWindow();
	void updateWindow();
	void renderWindow();
	void handleInput();
	void saveLevel();
private:
	int currentTile;
	RenderWindow window;
	Event event;
	Texture voidTexture;
	Texture wallTexture;
	Texture floorTexture;
	Sprite selectorVoid;
	Sprite selectorWall;
	Sprite selectorFloor;
	RectangleShape selectorBorder;
	RectangleShape saveButton;
	std::map<int, Texture> textureMap;
	std::vector<std::vector<int>> map;
	std::vector<std::vector<Sprite>> tiles;
};