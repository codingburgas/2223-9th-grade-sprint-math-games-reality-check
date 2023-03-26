#include "precompile.hpp"

class Tile {
private:
	Texture tileTexture;
	Sprite tileSprite;


public:
	void draw(RenderWindow& window);
	void setPosition(Vector2f position);
	void setTexture(Texture& tileTexture);
	void move(Vector2f offset);
	Vector2u position;

};