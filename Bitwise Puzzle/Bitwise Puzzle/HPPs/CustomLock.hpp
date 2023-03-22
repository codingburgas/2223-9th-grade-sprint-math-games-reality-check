#include "precompile.h"

class CustomLock {
private:
	Texture lockTexture;
	Sprite lockSprite;

public:
	int value;
	void unlock();
};