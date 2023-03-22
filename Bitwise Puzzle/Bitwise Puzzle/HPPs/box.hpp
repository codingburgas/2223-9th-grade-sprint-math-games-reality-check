#include "precompile.h"

class Box {
private:
	Texture boxTexture;
	Sprite boxSprite;

public:
	int value;
	void draw(RenderWindow& window);
	void setPosition(Vector2f position);
	void setTexture(Texture& boxTexture);
	void setValue(int value);
	void move(Vector2f offset);
	Vector2u position;
};