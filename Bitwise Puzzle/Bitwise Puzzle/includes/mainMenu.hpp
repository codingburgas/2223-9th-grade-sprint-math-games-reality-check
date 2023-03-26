#pragma once
#include "precompile.hpp";

class MainMenu
{
	private:
		Texture mainMenuTexture;
		Texture menuANDTexture;
		Texture menuORTexture;
		Texture menuXORTexture;
		Texture playTexture;
		Texture quitTexture;
		Sprite playSprite;
		Sprite quitSprite;
		Sprite mainMenuSprite;
		Sprite menuANDSprite;
		Sprite menuORSprite;
		Sprite menuXORSprite;
		Event ev;

	public:
		MainMenu(Vector2f position, RenderWindow& window);
		void drawMainMenu(RenderWindow& window);
		void update(RenderWindow& window);
		int mouseHandler(RenderWindow& window);
};