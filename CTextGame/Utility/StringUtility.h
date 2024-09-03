#pragma once

#include <string.h>

template <typename T, int row, int col>
bool StringSlice(const char* source, T(&outData)[row][col], const char* spliceValue = " ")
{
	unsigned short index = 0;
	char* context = nullptr;

	char* token = strtok_s((char*)source, spliceValue, &context);

	if (token == nullptr)
	{
		return false;
	}

	while (token != nullptr)
	{
		strcpy_s(outData[index++], token);
		token = strtok_s(context, spliceValue, &context);
	}
	return true;
}