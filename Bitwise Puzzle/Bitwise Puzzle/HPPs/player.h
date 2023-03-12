#pragma once
#include "precompile.h";

class Player
{
	public:
		void setTexture(Texture playerTexture);
		void move(Vector2f offset);
		void draw(RenderWindow& window);
		void updatePos();
		void setPosition(Vector2f position);
		Vector2i playerTile;
	private:
		Texture playerTexture;
		Sprite playerSprite;

		int x = 640;
		int y = 320;
};