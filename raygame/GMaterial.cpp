#include "GMaterial.h"

#include "MatManager.h"

GMaterial::GMaterial()
{
	posX = 0;
	posY = 0;
	color = BLANK;
	flamable = false;
	liquid = false;
	grain = false;
	density = 0;
	type = AIR;
	updatedFrame = false;
	updatedLine = false;
}


GMaterial::GMaterial(int X, int Y)
{
	posX = X;
	posY = Y;
	color = BLANK;
	flamable = false;
	liquid = false;
	grain = false;
	density = 0;
	type = AIR;
	updatedFrame = false;
	updatedLine = false;
}


GMaterial::~GMaterial()
{}

void GMaterial::Update(GMaterial***, int, int, MatManager&){}

bool GMaterial::CanUpdate()
{
	return (!updatedLine && !updatedFrame);
}