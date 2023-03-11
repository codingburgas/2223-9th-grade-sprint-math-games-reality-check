#include "precompile.h"

class game {
public:
	game(Vector2u size, string title);
	void drawWindow();
	void update();

private:
	RenderWindow window;
	CircleShape shape;
};