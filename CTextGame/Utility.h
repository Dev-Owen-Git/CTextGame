#pragma once

#include <string>

struct uvector2
{
	unsigned int x, y;
};

static const int RENDER_BUFFER_WIDTH_SIZE = 50;
static const int RENDER_BUFFER_HEIGHT_SIZE = 30;


static const int MAP_WITDH_SIZE = 40;
static const int MAP_HIGHT_SIZE = 30;

bool Colision(const uvector2& src, const uvector2& dest);

template <typename T, int row, int col>
bool StringSlice(const char* source, T(&outData)[row][col], const char* spliceValue = " ")
{
	unsigned short index = 0;
	char* context = nullptr;
	char* token = strtok_s((char*)source, spliceValue, &context);
	while (token != nullptr)
	{
		strcpy_s(outData[index], token);
		token = strtok_s(NULL, spliceValue, &context);
	}
	return true;
}