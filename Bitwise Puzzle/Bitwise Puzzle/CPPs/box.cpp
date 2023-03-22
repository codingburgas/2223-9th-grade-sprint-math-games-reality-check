#include "box.hpp"

void Box::draw(RenderWindow& window) {
	window.draw(this->boxSprite);
}

void Box::setPosition(Vector2f position) {
	this->boxSprite.setPosition(position);
	this->position.x = this->boxSprite.getPosition().x / 80;
	this->position.y = this->boxSprite.getPosition().y / 80;
}

void Box::setTexture(Texture& boxTexture) {
	this->boxSprite.setTexture(boxTexture);
}

void Box::setValue(int value) {
	this->value = value;
}

void Box::move(Vector2f offset) {
	this->boxSprite.move(offset);
	this->position.x = this->boxSprite.getPosition().x / 80;
	this->position.y = this->boxSprite.getPosition().y / 80;
}