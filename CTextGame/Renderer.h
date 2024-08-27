#pragma once

#include "Utility.h"

extern char renderBuffer[MAP_HIGHT_SIZE][MAP_WITDH_SIZE];

bool RendererInit();
bool ClearBuffer();

template<typename T>
bool CopyDataToRendBuffer(const uvector2 position, T value)
{
	::memcpy_s(&renderBuffer[position.y][position.x], MAP_WITDH_SIZE - position.x, (const void*)&value, sizeof(T));
	return true;
}

bool CopyDataToRendBuffer(const uvector2 position, char render);
bool CopyDataToRendBuffer(const uvector2 position, const char* render);

bool DrawBuffer();
void SetConsolePointer(uvector2 position);
bool NullTermimation();



