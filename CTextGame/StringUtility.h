#pragma once

#include <string.h>

template <typename T, int row, int col>
bool StringSlice(const char* source, T(&outData)[row][col], const char* spliceValue = " ")
{
	unsigned short index = 0;
	char* context = nullptr;

	char* token = strtok_s((char*)source, spliceValue, &context);

	while (token != nullptr)
	{
		strcpy_s(outData[index++], token);

		token = strtok_s(context, spliceValue, &context);
	}
	return true;
}

template<int srcBufferCount, int destBufferCount>
bool StringCompare(const char (&srcBuffer) [srcBufferCount], const char (&destBuffer) [destBufferCount])
{
	if (srcBufferCount > destBufferCount)
	{
		return false;
	}

	for (int i = 0; i < srcBufferCount; i++)
	{
		if (srcBuffer[i] != destBuffer[i])
		{
			return false;
		}
	}

	return true;
}