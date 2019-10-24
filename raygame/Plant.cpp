#include "Plant.h"
#include "MatManager.h"


Plant::Plant(int X, int Y) : Wall(X, Y)
{
	color = GREEN;
	flamable = true;
	liquid = false;
	density = 10;
	type = PLANT;
}


Plant::~Plant()
{}

void Plant::Update(GMaterial*** matList, int bottom, int side, MatManager& m)
{
	if (CanUpdate())
	{
		if (posY != bottom - 1)
		{
			if (matList[posY + 1][posX]->type == WATER)
			{
				m.PrepChange(posX, posY + 1, PLANT);
				matList[posY + 1][posX]->updatedFrame = true;
			}
		}
		if (matList[posY][posX - 1]->type == WATER)
		{
			m.PrepChange(posX - 1, posY, PLANT);
			matList[posY][posX - 1]->updatedFrame = true;
		}
		if (matList[posY][posX + 1]->type == WATER)
		{
			m.PrepChange(posX + 1, posY, PLANT);
			matList[posY][posX + 1]->updatedFrame = true;
		}
		if (matList[posY - 1][posX]->type == WATER)
		{
			m.PrepChange(posX, posY - 1, PLANT);
			matList[posY - 1][posX]->updatedFrame = true;
		}
	}
}