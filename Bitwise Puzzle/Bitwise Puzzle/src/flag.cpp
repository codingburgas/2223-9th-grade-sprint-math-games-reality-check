#include "flag.hpp"

void Flag::setProperties(Texture& texture, int imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	this->totalTime = 0.f;
	this->currentImage = 0;
	this->uvRect.width = texture.getSize().x / float(imageCount);
	this->uvRect.height = texture.getSize().y;
	this->uvRect.top = 0;
	this->body.setSize(sf::Vector2f(80, 80));
	this->body.setTexture(&texture);
}

void Flag::update(Time dt) {
	this->totalTime += dt.asSeconds();

	if (this->totalTime >= this->switchTime)
	{
		this->totalTime -= this->switchTime;
		this->currentImage++;

		if (this->currentImage >= this->imageCount)
		{
			this->currentImage = 0;
		}
	}

	this->uvRect.left = this->currentImage * this->uvRect.width;
	this->uvRect.width = abs(this->uvRect.width);

	this->body.setTextureRect(this->uvRect);
}

void Flag::draw(RenderWindow& window) {
	window.draw(this->body);
}

void Flag::setPosition(Vector2f position) {
	this->body.setPosition(position);
	this->position.x = position.x / 80;
	this->position.y = position.y / 80;

}