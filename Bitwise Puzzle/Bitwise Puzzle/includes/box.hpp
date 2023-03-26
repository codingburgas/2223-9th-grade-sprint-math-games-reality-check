#include "precompile.hpp"

class Box {
private:
	Texture boxTexture;
	Sprite boxSprite;

public:
	bool value;
	void draw(RenderWindow& window);
	void setPosition(Vector2f position);
	void setTexture(Texture& boxTexture);
	void setValue(bool value);
	void move(Vector2f offset);
	Vector2i position;
};