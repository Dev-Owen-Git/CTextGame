#pragma once

#include <Data/DataType.h>

bool RendererInit();
bool ClearBuffer();

bool NullTermimation();
void SetConsolePointer(vector2D<unsigned short> position);


bool CopyDataToRendBuffer(const vector2D<unsigned int> position, const char render);
bool CopyDataToRendBuffer(const vector2D<unsigned int> position, const char* render);


bool DrawBuffer();


