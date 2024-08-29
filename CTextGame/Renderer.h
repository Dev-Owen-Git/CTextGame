#pragma once

#include "DataType.h"

extern char renderBuffer[RENDER_BUFFER_HEIGHT_SIZE][RENDER_BUFFER_WIDTH_SIZE];

bool RendererInit();
bool ClearBuffer();

bool NullTermimation();
void SetConsolePointer(vector2D<unsigned int> position);


bool CopyDataToRendBuffer(const vector2D<unsigned int> position, const char render);
bool CopyDataToRendBuffer(const vector2D<unsigned int> position, const char* render);


bool DrawBuffer();


