#include "Wall.h"



Wall::Wall(int X, int Y) : GMaterial(X, Y)
{
	posX = X;
	posY = Y;
	color = GRAY;
	flamable = false;
	liquid = false;
	density = 10;
	type = WALL;
}


Wall::~Wall()
{}