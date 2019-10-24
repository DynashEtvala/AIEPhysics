#include "MatManager.h"

#include"MaterialIncludes.h"
#include<cmath>

MatManager::MatManager()
{
	changesReady = 0;
	height = -1;
	width = -1;
}

MatManager::MatManager(int h, int w)
{
	changesReady = 0;
	height = h;
	width = w;
}


MatManager::~MatManager()
{}


void MatManager::PrepChange(int X, int Y, MatType T)
{
	newMat[changesReady] = T;
	newPosX[changesReady] = X;
	newPosY[changesReady] = Y;
	changesReady++;
}

void MatManager::ExecuteChanges(GMaterial*** matList)
{
	for (int i = 0; i < changesReady; i++)
	{
		if (newPosX[i] >= 0 && newPosX[i] < width && newPosY[i] >= 0 && newPosY[i] < height)
		{
			bool frameHold = matList[newPosY[i]][newPosX[i]]->updatedFrame;
			delete matList[newPosY[i]][newPosX[i]];
			switch (newMat[i])
			{
			case AIR:
			default:
				matList[newPosY[i]][newPosX[i]] = new GMaterial(newPosX[i], newPosY[i]);
				break;
			case WALL:
				matList[newPosY[i]][newPosX[i]] = new Wall(newPosX[i], newPosY[i]);
				break;
			case WATER:
				matList[newPosY[i]][newPosX[i]] = new Water(newPosX[i], newPosY[i]);
				matList[newPosY[i]][newPosX[i]]->updatedLine = true;
				break;
			case SAND:
				matList[newPosY[i]][newPosX[i]] = new Sand(newPosX[i], newPosY[i]);
				matList[newPosY[i]][newPosX[i]]->updatedLine = true;
				break;
			case OIL:
				matList[newPosY[i]][newPosX[i]] = new Oil(newPosX[i], newPosY[i]);
				matList[newPosY[i]][newPosX[i]]->updatedLine = true;
				break;
			case SALT:
				matList[newPosY[i]][newPosX[i]] = new Salt(newPosX[i], newPosY[i]);
				matList[newPosY[i]][newPosX[i]]->updatedLine = true;
				break;
			case SALTWATER:
				matList[newPosY[i]][newPosX[i]] = new SaltWater(newPosX[i], newPosY[i]);
				matList[newPosY[i]][newPosX[i]]->updatedLine = true;
				break;
			case PLANT:
				matList[newPosY[i]][newPosX[i]] = new Plant(newPosX[i], newPosY[i]);
				matList[newPosY[i]][newPosX[i]]->updatedLine = true;
				break;
			}
			if (matList[newPosY[i]][newPosX[i]]->liquid || matList[newPosY[i]][newPosX[i]]->grain)
			{
				matList[newPosY[i]][newPosX[i]]->updatedFrame = frameHold;
			}
		}
	}
	changesReady = 0;
}

void MatManager::ClearUpdatesLine(GMaterial*** matList, int row, int side)
{
	for (int j = 0; j < side; j++)
	{
		matList[row][j]->updatedLine = false;
	}
}

void MatManager::ClearUpdatesFrame(GMaterial*** matList, int bottom, int side)
{
	for (int i = 0; i < bottom; i++)
	{
		for (int j = 0; j < side; j++)
		{
			if (!(j == 0 || j == 1 || j == width - 1 || j == width - 2))
			{
				matList[i][j]->updatedFrame = false;
			}
		}
	}
}

void MatManager::PaintCircle(GMaterial*** matList, int X0, int Y0, int radius, MatType type)
{
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		if (true)
		{
			PaintLine(matList, X0 + x, Y0 + y, X0 - x, Y0 + y, type);
			PaintLine(matList, X0 + y, Y0 + x, X0 + y, Y0 - x, type);
			PaintLine(matList, X0 - y, Y0 + x, X0 - y, Y0 - x, type);
			PaintLine(matList, X0 - x, Y0 - y, X0 + x, Y0 - y, type);
		}

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void MatManager::PaintCircleOutline(GMaterial*** matList, int X0, int Y0, int radius, MatType type)
{
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		if (true)
		{
			PaintMaterial(matList, X0 + x, Y0 + y, type);
			PaintMaterial(matList, X0 - x, Y0 + y, type);
			PaintMaterial(matList, X0 + x, Y0 - y, type);
			PaintMaterial(matList, X0 - x, Y0 - y, type);
			PaintMaterial(matList, X0 + y, Y0 + x, type);
			PaintMaterial(matList, X0 - y, Y0 + x, type);
			PaintMaterial(matList, X0 + y, Y0 - x, type);
			PaintMaterial(matList, X0 - y, Y0 - x, type);
		}

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void MatManager::PaintLineLow(GMaterial*** matList, int X1, int Y1, int X2, int Y2, MatType type)
{
	int dx = X2 - X1;
	int dy = Y2 - Y1;
	int yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	int D = 2 * dy - dx;
	int y = Y1;

	for (int x = X1; x <= X2; x++)
	{
		PaintMaterial(matList, x, y, type);
		if (D > 0)
		{
			y = y + yi;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
	}
}

void MatManager::PaintLineHigh(GMaterial*** matList, int X1, int Y1, int X2, int Y2, MatType type)
{
	int dx = X2 - X1;
	int dy = Y2 - Y1;
	int xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	int D = 2 * dx - dy;
	int x = X1;

	for (int y = Y1; y <= Y2; y++)
	{
		PaintMaterial(matList, x, y, type);
		if (D > 0)
		{
			x = x + xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
	}
}

void MatManager::PaintLine(GMaterial*** matList, int X1, int Y1, int X2, int Y2, MatType type)
{
	if (abs(Y2 - Y1) < abs(X2 - X1))
	{
		if (X1 > X2)
		{
			PaintLineLow(matList, X2, Y2, X1, Y1, type);
		}
		else
		{
			PaintLineLow(matList, X1, Y1, X2, Y2, type);
		}
	}
	else
	{
		if (Y1 > Y2)
		{
			PaintLineHigh(matList, X2, Y2, X1, Y1, type);
		}
		else
		{
			PaintLineHigh(matList, X1, Y1, X2, Y2, type);
		}
	}
}

void MatManager::PaintCircleLineLow(GMaterial*** matList, int X1, int Y1, int X2, int Y2, int radius, MatType type)
{
	int dx = X2 - X1;
	int dy = Y2 - Y1;
	int yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	int D = 2 * dy - dx;
	int y = Y1;

	for (int x = X1; x <= X2; x++)
	{
		/*
		if (x == X1 || x == X2)
		{
			PaintCircle(matList, x, y, radius, type);
		}
		else
		{
			PaintCircleOutline(matList, x, y, radius, type);
		}
		*/

		PaintCircle(matList, x, y, radius, type);

		if (D > 0)
		{
			y = y + yi;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
	}
}

void MatManager::PaintCircleLineHigh(GMaterial*** matList, int X1, int Y1, int X2, int Y2, int radius, MatType type)
{
	int dx = X2 - X1;
	int dy = Y2 - Y1;
	int xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	int D = 2 * dx - dy;
	int x = X1;

	for (int y = Y1; y <= Y2; y++)
	{
		if (y == Y1 || y == Y2)
		{
			PaintCircle(matList, x, y, radius, type);
		}
		else
		{
			PaintCircleOutline(matList, x, y, radius, type);
		}
		if (D > 0)
		{
			x = x + xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
	}
}

void MatManager::PaintCircleLine(GMaterial*** matList, int X1, int Y1, int X2, int Y2, int radius, MatType type)
{
	if (abs(Y2 - Y1) < abs(X2 - X1))
	{
		if (X1 > X2)
		{
			PaintCircleLineLow(matList, X2, Y2, X1, Y1, radius, type);
		}
		else
		{
			PaintCircleLineLow(matList, X1, Y1, X2, Y2, radius, type);
		}
	}
	else
	{
		if (Y1 > Y2)
		{
			PaintCircleLineHigh(matList, X2, Y2, X1, Y1, radius, type);
		}
		else
		{
			PaintCircleLineHigh(matList, X1, Y1, X2, Y2, radius, type);
		}
	}
}

void MatManager::PaintMaterial(GMaterial*** matList, int X, int Y, MatType type)
{
	if (X >= 2 && X < width - 2 && Y >= 0 && Y < height && matList[Y][X]->type != type)
	{
		delete matList[Y][X];
		switch (type)
		{
		case AIR:
		default:
			matList[Y][X] = new GMaterial(X, Y);
			break;
		case WALL:
			matList[Y][X] = new Wall(X, Y);
			break;
		case WATER:
			matList[Y][X] = new Water(X, Y);
			break;
		case SAND:
			matList[Y][X] = new Sand(X, Y);
			break;
		case OIL:
			matList[Y][X] = new Oil(X, Y);
			break;
		case SALT:
			matList[Y][X] = new Salt(X, Y);
			break;
		case PLANT:
			matList[Y][X] = new Plant(X, Y);
			break;
		}
	}
}

void MatManager::PrintMatInfo(GMaterial*** matList, int X, int Y)
{
	
}