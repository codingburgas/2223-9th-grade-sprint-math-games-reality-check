#include "precompile.h"

class CustomLock {
private:
	Texture lockTexture;
	Sprite lockSprite;

public:
	bool value;
	bool drawable;
	Vector2u position;
	void draw(RenderWindow& window);
	void setPosition(Vector2f position);
	void setTexture(Texture& lockTexture);
	void setValue(bool value);
	void fadeOut();
};