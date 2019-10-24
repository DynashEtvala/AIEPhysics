#include "Liquid.h"

#include "MatManager.h"

Liquid::Liquid(int X, int Y) : GMaterial(X, Y)
{
	liquid = true;
	density = 1.0f;
}


Liquid::~Liquid()
{}


void Liquid::Update(GMaterial*** matList, int bottom, int side, MatManager& m)
{
	if (CanUpdate())
	{
		if (posY == bottom - 1)
		{
			m.PrepChange(posX, posY, AIR);
		}
		else if ((matList[posY + 1][posX]->CanUpdate()) && matList[posY + 1][posX]->density < density)
		{
			m.PrepChange(posX, posY, matList[posY + 1][posX]->type);
			updatedFrame = true;
			m.PrepChange(posX, posY + 1, type);
		}
		else if ((matList[posY + 1][posX + 1]->density < density && matList[posY][posX + 1]->density < density) || (matList[posY + 1][posX - 1]->density < density && matList[posY][posX - 1]->density < density))
		{
			if ((matList[posY + 1][posX + 1]->CanUpdate() && matList[posY + 1][posX + 1]->density < density && matList[posY][posX + 1]->density < density) && (matList[posY + 1][posX - 1]->CanUpdate() && matList[posY + 1][posX - 1]->density < density && matList[posY][posX - 1]->density < density))
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
			else if (matList[posY + 1][posX + 1]->CanUpdate() && matList[posY + 1][posX + 1]->density < density && matList[posY][posX + 1]->density < density)
			{
				m.PrepChange(posX, posY, matList[posY + 1][posX + 1]->type);
				updatedFrame = true;
				m.PrepChange(posX + 1, posY + 1, type);
			}
			else if (matList[posY + 1][posX - 1]->CanUpdate() && matList[posY + 1][posX - 1]->density < density && matList[posY][posX - 1]->density < density)
			{
				m.PrepChange(posX, posY, matList[posY + 1][posX - 1]->type);
				updatedFrame = true;
				m.PrepChange(posX - 1, posY + 1, type);
			}
		}
		else if (CanFlatten(matList) || CanFlatten(matList, side))
		{
			bool left = CanFlatten(matList);
			bool right = CanFlatten(matList, side);
			if ((matList[posY][posX - 1]->CanUpdate() && left) && (matList[posY][posX + 1]->CanUpdate() && right))
			{
				if (GetRandomValue(0, 1))
				{
					m.PrepChange(posX, posY, matList[posY][posX + 1]->type);
					m.PrepChange(posX + 1, posY, type);
				}
				else
				{
					m.PrepChange(posX, posY, matList[posY][posX - 1]->type);
					m.PrepChange(posX - 1, posY, type);
				}
			}
			else if (matList[posY][posX - 1]->CanUpdate() && left)
			{
				m.PrepChange(posX, posY, matList[posY][posX - 1]->type);
				m.PrepChange(posX - 1, posY, type);
			}
			else if (matList[posY][posX + 1]->CanUpdate() && right)
			{
				m.PrepChange(posX, posY, matList[posY][posX + 1]->type);
				m.PrepChange(posX + 1, posY, type);
			}
		}
	}
}

bool Liquid::CanFlatten(GMaterial*** matList)
{
	for (int i = posX; i > 0; i--)
	{
		if (matList[posY + 1][i]->density >= density)
		{
			continue;
		}
		else
		{
			for (int j = i; j < posX; j++)
			{
				if (matList[posY][j]->density >= 9)
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

bool Liquid::CanFlatten(GMaterial*** matList, int side)
{
	for (int i = posX; i < side; i++)
	{
		if (matList[posY + 1][i]->density >= density)
		{
			continue;
		}
		else
		{
			for (int j = i; j > posX; j--)
			{
				if (matList[posY][j]->density >= 9)
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
}