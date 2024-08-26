#pragma once

#include <string>

struct uvector2
{
	unsigned int x, y;
};

static const int MAP_HIGHT_SIZE = 30;
static const int MAP_WITDH_SIZE = 40;

bool Colision(const uvector2& src, const uvector2& dest);

template <typename T, int row, int col>
bool StringSlice(const char* source, T(*&outData)[row][col], const char* spliceValue = " ")
{
	unsigned short index = 0;
	char* sliceStr = strtok((char*)source, spliceValue);
	while (sliceStr != nullptr)
	{
		strcpy_s(outData[index], sliceStr);
		sliceStr = strtok(NULL, spliceValue);
	}
	return true;
}