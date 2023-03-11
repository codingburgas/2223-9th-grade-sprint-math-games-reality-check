#pragma once
#include "precompile.h";

class Player
{
	public:
		int moveUP();
		int moveDown();
		int moveLeft();
		int moveRight();
	private:
		int x = 600;
		int y = 360;
};