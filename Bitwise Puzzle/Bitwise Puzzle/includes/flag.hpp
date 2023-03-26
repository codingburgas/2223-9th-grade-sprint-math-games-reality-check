#include "precompile.hpp"

class Flag {
private:
	float totalTime;
	float switchTime;
	int currentImage;
	int imageCount;

public:
	void setProperties(Texture& texture, int imageCount, float switchTime);
	void update(Time dt);
	void draw(RenderWindow& window);
	void setPosition(Vector2f position);

	Vector2u position;
	IntRect uvRect;
	RectangleShape body;
};