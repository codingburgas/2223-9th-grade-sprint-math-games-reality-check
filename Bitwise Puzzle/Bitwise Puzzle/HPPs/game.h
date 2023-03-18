#include "precompile.h"
#include "tile.hpp"
#include "mainMenu.h"
#include "player.h"

class game {
public:
	game(Vector2u size, string title);
	void drawWindow();
	void update();
	void processKeyPressed();
	void animatePlayerMovement(int xChange, int yChange);
	void loadLevel(string level);
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
	Tile attachedBoxes[4];
	map<int, Texture> textureMap;
	vector<vector<int>> level;
	vector<vector<Tile>> tiles;
};