#include "SaltWater.h"



SaltWater::SaltWater(int X, int Y) : Water(X, Y)
{
	color = SKYBLUE;
	flamable = false;
	liquid = true;
	density = 1.58;
	type = SALTWATER;
}


SaltWater::~SaltWater()
{}
