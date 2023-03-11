#include "tile.hpp"

void Tile::draw(RenderWindow& window) {
	window.draw(this->tileSprite);
}

void Tile::setPosition(Vector2f position) {
	this->tileSprite.setPosition(position);
}

void Tile::setTexture(Texture& tileTexture) {
	this->tileSprite.setTexture(tileTexture);
}