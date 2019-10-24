#pragma once
#include "GMaterial.h"
class Grain :
	public GMaterial
{
public:
	Grain(int X, int Y);
	~Grain();
	void Update(GMaterial***, int, int, class MatManager&);
};

