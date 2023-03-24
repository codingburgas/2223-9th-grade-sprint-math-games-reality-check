#include "CustomLock.hpp"

void CustomLock::draw(RenderWindow& window) {
	window.draw(this->lockSprite);
}

void CustomLock::setPosition(Vector2f position) {
	this->lockSprite.setPosition(position);
	this->position.x = position.x / 80;
	this->position.y = position.y / 80;
}

void CustomLock::setTexture(Texture& lockTexture) {
	this->lockSprite.setTexture(lockTexture);
	this->drawable = true;
}

void CustomLock::setValue(bool value) {
	this->value = value;
}

void CustomLock::fadeOut() {
	Color lockColor = this->lockSprite.getColor();
	Vector2f lockScale = this->lockSprite.getScale();

	this->lockSprite.setOrigin(40, 40);
	this->lockSprite.move(40, 40);

	while (lockColor.a > 3) {
		lockColor = this->lockSprite.getColor();
		lockScale = this->lockSprite.getScale();

		this->lockSprite.setColor(Color(lockColor.r, lockColor.g, lockColor.b, lockColor.a - 2));
		this->lockSprite.setScale(Vector2f(lockScale.x + 0.016, lockScale.y + 0.016));
		sleep(Time(milliseconds(1)));
	}

	this->drawable = false;
}