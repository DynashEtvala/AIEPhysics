#pragma once
#include "Wall.h"
class Plant :
	public Wall
{
public:
	Plant(int, int);
	~Plant();
	void Update(GMaterial***, int, int, class MatManager&);
};

