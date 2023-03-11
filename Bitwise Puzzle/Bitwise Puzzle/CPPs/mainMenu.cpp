#include "mainMenu.h"

MainMenu::MainMenu(Texture mainMenuTexture, Vector2f position, RenderWindow& window)
{
	this->mainMenuSprite.setTexture(mainMenuTexture);
	this->mainMenuSprite.setPosition(position);
	update(window);
}

void MainMenu::update(RenderWindow& window)
{
	drawMainMenu(window);
}

void MainMenu::drawMainMenu(RenderWindow& window)
{
	window.draw(this->mainMenuSprite);
}