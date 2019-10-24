#pragma once
#include"Global.h"

class MatManager
{
private:
	MatType newMat[25];
	int height;
	int width;
	int newPosX[25];
	int newPosY[25];
	int changesReady;
public:
	MatManager();
	MatManager(int, int);
	~MatManager();
	void PrepChange(int, int, MatType);
	void ExecuteChanges(class GMaterial***);
	void ClearUpdatesLine(class GMaterial***, int, int);
	void ClearUpdatesFrame(class GMaterial***, int, int);
	void PaintCircle(GMaterial***, int, int, int, MatType);
	void PaintCircleOutline(GMaterial*** matList, int X0, int Y0, int radius, MatType type);

	void PaintLineLow(GMaterial***, int, int, int, int, MatType);
	void PaintLineHigh(GMaterial***, int, int, int, int, MatType);
	void PaintLine(GMaterial***, int, int, int, int, MatType);

	void PaintCircleLineLow(GMaterial***, int, int, int, int, int, MatType);
	void PaintCircleLineHigh(GMaterial***, int, int, int, int, int, MatType);
	void PaintCircleLine(GMaterial***, int, int, int, int, int, MatType);

	void PaintMaterial(class GMaterial***, int, int, MatType);
	void PrintMatInfo(class GMaterial***, int, int);
};

