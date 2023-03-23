#include "precompile.h"

class CustomLock {
private:
	Texture lockTexture;
	Sprite lockSprite;

public:
	bool value;
	void draw(RenderWindow& window);
	void setPosition(Vector2f position);
	void setTexture(Texture& lockTexture);
	void setValue(bool value);
	void fadeOut();
};