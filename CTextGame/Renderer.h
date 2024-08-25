#pragma once

#include "Utility.h"

bool RendererInit();
bool ClearBuffer();
bool CopyDataToRendBuffer(const uvector2 position, char render);
bool CopyDataToRendBuffer(const uvector2 position, const char* render);

bool DrawBuffer();
void SetConsolePointer(uvector2 position);
bool NullTermimation();



extern char renderBuffer[MAP_HIGHT_SIZE][MAP_WITDH_SIZE];
