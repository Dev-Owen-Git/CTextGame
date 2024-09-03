#pragma once

#include "DataType.h"
static const double PI = 3.141592;

static double Degree2Radian(int degree)
{
	return  degree * PI / 180.0f;
}

template<typename type>
vector2D<type> Normalize(vector2D<type>* value)
{
	if (value->x != 0)
	{
		value->x /= 1;
	}

	if (value->y != 0)
	{
		value->y /= 1;
	}

	return (*value);
}


template<typename type>
vector2D<type> GetNormalizeDiraction(const int degree)
{
	const double radion = Degree2Radian(degree);

	vector2D<type> rtnDir;
	rtnDir.x = cos(radion);
	rtnDir.y = sin(radion);

	Normalize(&rtnDir);

	return rtnDir;
}

