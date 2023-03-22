#include "CustomLock.hpp"
#include <thread>

void CustomLock::draw(RenderWindow& window) {
	window.draw(this->lockSprite);
}

void CustomLock::setPosition(Vector2f position) {
	this->lockSprite.setPosition(position);
}

void CustomLock::setTexture(Texture& lockTexture) {
	this->lockSprite.setTexture(lockTexture);
}

void CustomLock::setValue(int value) {
	this->value = value;
}

void CustomLock::fadeOut() {
	Color lockColor = this->lockSprite.getColor();

	while (lockColor.a > 3) {
		lockColor = this->lockSprite.getColor();
		this->lockSprite.setColor(Color(lockColor.r, lockColor.g, lockColor.b, lockColor.a - 2));
		sleep(Time(milliseconds(1)));
	}
}