#include "precompile.h"

class CustomLock {
private:
	Texture lockTexture;
	Sprite lockSprite;

public:
	int value;
	void draw(RenderWindow& window);
	void setPosition(Vector2f position);
	void setTexture(Texture& lockTexture);
	void setValue(int value);
	void fadeOut();
};