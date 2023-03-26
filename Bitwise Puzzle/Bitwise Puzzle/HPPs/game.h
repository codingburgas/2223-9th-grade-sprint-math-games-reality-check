#include "precompile.h"
#include "tile.hpp"
#include "mainMenu.h"
#include "player.h"
#include "box.hpp"
#include "CustomLock.hpp"
#include "flag.hpp"

class game {
public:
	game(Vector2u size, string title);
	void drawWindow();
	void update();
	void processKeyPressed();
	void animatePlayerMovement(int xChange, int yChange);
	void loadLevel(string level);
	void checkForAdjacentBoxes();
	void checkForUnlock();
	void animateBoxRotation(char key);
	void rotateE();
	void rotateQ();
private:
	RenderWindow window;
	Texture voidTexture;
	Texture wallTexture;
	Texture floorTexture;
	Texture flagTexture;
	Texture mainMenuTexture;
	Texture plrTexture;
	Texture box0Texture;
	Texture box1Texture;
	Texture lock0Texture;
	Texture lock1Texture;
	Texture ANDTexture;
	Texture ORTexture;
	Texture XORTexture;
	Event event;
	Player plr;
	Flag flag;
	Clock clock;
	Time dt;
	map<int, Texture> textureMap;
	map<int, Texture> plrTextures;
	vector<Box> boxes;
	vector<Box*> attachedBoxes;
	vector<CustomLock> locks;
	vector<vector<int>> level;
	vector<vector<Tile>> tiles;
	vector<Vector2f> positions;

	bool canMove;
	bool windowShouldClose;
	int currentLevel;
};