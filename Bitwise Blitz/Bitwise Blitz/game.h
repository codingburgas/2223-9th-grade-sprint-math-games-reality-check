#include "precompile.h"
#include "bigLevel.h"

class game {
public:
	game(Vector2u size, string title);
	void drawWindow();
	void update();


private:
	//CircleShape shape;
	RenderWindow window; 
	bigLevel mainLevel;
};