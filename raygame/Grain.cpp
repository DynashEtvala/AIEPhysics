#include "Grain.h"

#include "MatManager.h"

Grain::Grain(int X, int Y) : GMaterial(X, Y)
{
	grain = true;
	density = 9;
}


Grain::~Grain()
{}

void Grain::Update(GMaterial*** matList, int bottom, int side, MatManager& m)
{
	if (CanUpdate())
	{
		if (posY == bottom - 1)
		{
			m.PrepChange(posX, posY, AIR);
		}
		else if ((matList[posY + 1][posX]->liquid ? matList[posY + 1][posX]->CanUpdate() : true) && matList[posY + 1][posX]->density < density)
		{
			m.PrepChange(posX, posY, matList[posY + 1][posX]->type);
			updatedFrame = true;
			m.PrepChange(posX, posY + 1, type);
		}
		else if ((matList[posY + 1][posX + 1]->density < density && matList[posY][posX + 1]->density < density) || (matList[posY + 1][posX - 1]->density < density && matList[posY][posX - 1]->density < density))
		{
			if (((matList[posY + 1][posX + 1]->liquid ? matList[posY + 1][posX + 1]->CanUpdate() : true) && matList[posY + 1][posX + 1]->density < density && matList[posY][posX + 1]->density < density) && ((matList[posY + 1][posX - 1]->liquid ? matList[posY + 1][posX - 1]->CanUpdate() : true) && matList[posY + 1][posX - 1]->density < density && matList[posY][posX - 1]->density < density))
			{
				if (GetRandomValue(0, 1))
				{
					m.PrepChange(posX, posY, matList[posY + 1][posX + 1]->type);
					updatedFrame = true;
					m.PrepChange(posX + 1, posY + 1, type);
				}
				else
				{
					m.PrepChange(posX, posY, matList[posY + 1][posX - 1]->type);
					updatedFrame = true;
					m.PrepChange(posX - 1, posY + 1, type);
				}
			}
			else if ((matList[posY + 1][posX + 1]->liquid ? matList[posY + 1][posX + 1]->CanUpdate() : true) && matList[posY + 1][posX + 1]->density < density && matList[posY][posX + 1]->density < density)
			{
				m.PrepChange(posX, posY, matList[posY + 1][posX + 1]->type);
				updatedFrame = true;
				m.PrepChange(posX + 1, posY + 1, type);
			}
			else if ((matList[posY + 1][posX - 1]->liquid ? matList[posY + 1][posX - 1]->CanUpdate() : true) && matList[posY + 1][posX - 1]->density < density && matList[posY][posX - 1]->density < density)
			{
				m.PrepChange(posX, posY, matList[posY + 1][posX - 1]->type);
				updatedFrame = true;
				m.PrepChange(posX - 1, posY + 1, type);
			}
		}
	}
}