#include "precompile.h"

class Box {
private:
	Texture boxTexture;
	Sprite boxSprite;

public:
	void draw(RenderWindow& window);
	void setPosition(Vector2f position);
	void setTexture(Texture& boxTexture);
	void move(Vector2f offset);
	Vector2u position;
};