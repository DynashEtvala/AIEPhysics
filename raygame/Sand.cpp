#include "Sand.h"



Sand::Sand(int X, int Y) : Grain(X, Y)
{
	color = BEIGE;
	flamable = false;
	liquid = false;
	type = SAND;
}


Sand::~Sand()
{}
