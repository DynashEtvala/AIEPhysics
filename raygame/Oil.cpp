#include "Oil.h"



Oil::Oil(int X, int Y) : Liquid(X, Y)
{
	color = DARKBROWN;
	flamable = true;
	liquid = true;
	density = 0.93;
	type = OIL;
}


Oil::~Oil()
{}
