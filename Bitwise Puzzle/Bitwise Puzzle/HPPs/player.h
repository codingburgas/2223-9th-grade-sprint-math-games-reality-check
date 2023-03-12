#pragma once
#include "precompile.h";

class Player
{
	public:
		void setTexture(Texture playerTexture);
		void move(Vector2f offset);
		void draw(RenderWindow& window);
		void updatePos();
	private:
		Texture playerTexture;
		Sprite playerSprite;

		int x = 640;
		int y = 320;
		Vector2i playerTile;
};