#pragma once
#include "Grain.h"
class Salt :
	public Grain
{
public:
	Salt(int, int);
	~Salt();
	void Update(GMaterial***, int, int, class MatManager&);
};

