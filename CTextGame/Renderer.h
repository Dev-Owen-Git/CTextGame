#pragma once

#include "Utility.h"

extern char renderBuffer[RENDER_BUFFER_HEIGHT_SIZE][RENDER_BUFFER_WIDTH_SIZE];

bool RendererInit();
bool ClearBuffer();

bool NullTermimation();
void SetConsolePointer(uvector2 position);


bool CopyDataToRendBuffer(const uvector2 position, char render);
bool CopyDataToRendBuffer(const uvector2 position, const char* render);


bool DrawBuffer();


