#include "precompile.hpp"

class App {
public:
	void initWindow();
	void updateWindow();
	void renderWindow();
	void handleInput();
private:
	RenderWindow window;
	Event event;
	Texture wallTexture;
	Texture voidTexture;
	Texture floorTexture;
	std::map<int, Texture> textureMap;
	std::vector<std::vector<int>> map;
	std::vector<std::vector<Sprite>> tiles;
};