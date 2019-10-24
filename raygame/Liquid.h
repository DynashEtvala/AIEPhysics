#pragma once
#include "GMaterial.h"
class Liquid :
	public GMaterial
{
public:
	Liquid(int, int);
	~Liquid();
	void Update(GMaterial***, int, int, class MatManager&);
	bool CanFlatten(GMaterial***);
	bool CanFlatten(GMaterial***, int);
};

