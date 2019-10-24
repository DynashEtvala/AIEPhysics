#pragma once

struct Point
{
	int X;
	int Y;
};

int ExpoGrow(int val, int exp)
{
	int result = 1;
	while (exp > 0)
	{
		result *= val;
		exp--;
	}
	return result;
}