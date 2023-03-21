#include "precompile.h"
#include "tile.hpp"
#include "mainMenu.h"
#include "player.h"
#include "box.hpp"

class game {
public:
	game(Vector2u size, string title);
	void drawWindow();
	void update();
	void processKeyPressed();
	void animatePlayerMovement(int xChange, int yChange);
	void loadLevel(string level);
	void checkForAdjacentBoxes();
private:
	RenderWindow window;
	Texture voidTexture;
	Texture wallTexture;
	Texture floorTexture;
	Texture mainMenuTexture;
	Texture plrTexture;
	Texture boxTexture;
	Event event;
	Player plr;
	map<int, Texture> textureMap;
	vector<Box> boxes;
	vector<Box*> attachedBoxes;
	vector<vector<int>> level;
	vector<vector<Tile>> tiles;

	bool hasBox;
	bool canMove;
};