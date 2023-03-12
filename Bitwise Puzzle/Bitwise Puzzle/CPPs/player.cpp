#include "player.h";

void Player::setTexture(Texture playerTexture) {
	this->playerTexture.swap(playerTexture);
	this->playerSprite.setTexture(this->playerTexture);

}

void Player::move(Vector2f offset) {
	this->playerSprite.move(offset);
	updatePos();
}

void Player::draw(RenderWindow& window) {
	window.draw(this->playerSprite);
}

void Player::updatePos() {
	this->x = this->playerSprite.getPosition().x;
	this->y = this->playerSprite.getPosition().y;
	this->playerTile.x = this->x / 80;
	this->playerTile.y = this->y / 80;
}