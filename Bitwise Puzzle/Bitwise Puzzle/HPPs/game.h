#include "precompile.h"
#include "tile.hpp"

class game {
public:
	game(Vector2u size, string title);
	void drawWindow();
	void update();

private:
	RenderWindow window;
	Texture tileTexture;
	vector<vector<Tile>> tiles;

};