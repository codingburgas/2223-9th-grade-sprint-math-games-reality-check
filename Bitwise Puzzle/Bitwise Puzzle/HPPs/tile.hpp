#include "precompile.h"

class Tile {
private:
	Texture tileTexture;
	Sprite tileSprite;

public:
	void draw(RenderWindow& window);
	void setPosition(Vector2f position);
	void setTexture(Texture& tileTexture);

};