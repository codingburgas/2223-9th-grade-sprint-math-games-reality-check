#include "tile.hpp"

void Tile::draw(RenderWindow& window) {
	window.draw(this->tileSprite);
}

void Tile::setPosition(Vector2f position) {
	this->tileSprite.setPosition(position);
	this->position.x = this->tileSprite.getPosition().x / 80;
	this->position.y = this->tileSprite.getPosition().y / 80;
}

void Tile::setTexture(Texture& tileTexture) {
	this->tileSprite.setTexture(tileTexture);
}

void Tile::move(Vector2f offset) {
	this->tileSprite.move(offset);
	this->position.x = this->tileSprite.getPosition().x / 80;
	this->position.y = this->tileSprite.getPosition().y / 80;
}