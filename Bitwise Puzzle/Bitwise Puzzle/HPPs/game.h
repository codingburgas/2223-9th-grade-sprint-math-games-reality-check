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
	Texture wallTexture;
	Texture floorTexture;
	Texture voidTexture;
	vector<vector<Tile>> tiles;
	Texture mainMenuTexture;
	Texture plrTexture;
	Event event;
	Player plr;
	map<int, Texture> textureMap;
	vector<vector<int>> level;
};