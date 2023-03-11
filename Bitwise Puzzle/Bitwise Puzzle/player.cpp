#include "player.h";

int Player::moveDown()
{
	return this->y += 80;
}
int Player::moveUP()
{
	return this->y -= 80;
}
int Player::moveLeft()
{
	return this->x -= 80;
}
int Player::moveRight()
{
	return this->x += 80;
}