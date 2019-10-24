#pragma once
#include"Global.h"

class GMaterial
{
public:
	int posX;
	int posY;
	Color color;
	bool liquid;
	bool grain;
	bool flamable;
	bool updatedFrame;
	bool updatedLine;
	float density;
	MatType type;
	GMaterial();
	GMaterial(int, int);
	~GMaterial();
	virtual void Update(GMaterial***, int, int, class MatManager&);
	bool CanUpdate();
};

