#pragma once
#include "precompile.h";

class MainMenu
{
	private:
		Texture mainMenuTexture;
		Sprite mainMenuSprite;
	public:
		MainMenu(Texture mainMenuTexture, Vector2f position, RenderWindow& window);
		void drawMainMenu(RenderWindow& window);
		void update(RenderWindow& window);
};