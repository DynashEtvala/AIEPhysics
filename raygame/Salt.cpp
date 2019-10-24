#include "Salt.h"
#include "MatManager.h"


Salt::Salt(int X, int Y) : Grain(X, Y)
{
	color = LIGHTGRAY;
	flamable = false;
	liquid = false;
	type = SALT;
}


Salt::~Salt()
{}


void Salt::Update(GMaterial*** matList, int bottom, int side, MatManager& m)
{
	Grain::Update(matList, bottom, side, m);
	if (posY != bottom - 1)
	{
		if (matList[posY + 1][posX]->type == WATER)
		{
			m.PrepChange(posX, posY, SALTWATER);
			m.PrepChange(posX, posY + 1, SALTWATER);
		}
		else if (matList[posY][posX + 1]->type == WATER && matList[posY][posX - 1]->type == WATER)
		{
			if (GetRandomValue(0, 1))
			{
				m.PrepChange(posX, posY, SALTWATER);
				m.PrepChange(posX - 1, posY, SALTWATER);
			}
			else
			{
				m.PrepChange(posX, posY, SALTWATER);
				m.PrepChange(posX + 1, posY, SALTWATER);
			}
		}
		else if (matList[posY][posX - 1]->type == WATER)
		{
			m.PrepChange(posX, posY, SALTWATER);
			m.PrepChange(posX - 1, posY, SALTWATER);
		}
		else if (matList[posY][posX + 1]->type == WATER)
		{
			m.PrepChange(posX, posY, SALTWATER);
			m.PrepChange(posX + 1, posY, SALTWATER);
		}
		else if (matList[posY - 1][posX]->type == WATER)
		{
			m.PrepChange(posX, posY, SALTWATER);
			m.PrepChange(posX, posY - 1, SALTWATER);
		}
	}
}