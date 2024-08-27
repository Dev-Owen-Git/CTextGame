#include "Renderer.h"

#include "FrameRate.h"

#include <windows.h>
#include <stdio.h>

char renderBuffer[RENDER_BUFFER_HEIGHT_SIZE][RENDER_BUFFER_WIDTH_SIZE] = { ' ',};

HANDLE cursorPointerHandler;

bool RendererInit()
{
    CONSOLE_CURSOR_INFO cursorInfo;

    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;

    cursorPointerHandler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(cursorPointerHandler, &cursorInfo);

    return true;
}

bool ClearBuffer()
{
    ::memset(renderBuffer, ' ', sizeof(renderBuffer));
    return true;
}



bool CopyDataToRendBuffer(const uvector2 position, char render)
{
    renderBuffer[position.y][position.x] = render;
    return true;
}

bool CopyDataToRendBuffer(const uvector2 position, const char* render)
{
    const int copySize = strlen(render);
    const int remingSize = RENDER_BUFFER_WIDTH_SIZE - copySize;
    ::memcpy_s(&renderBuffer[position.y][position.x], remingSize, (const void*) render, copySize);
    return true;
}

bool DrawBuffer()
{
    NullTermimation();

    for (unsigned int y = 0; y < RENDER_BUFFER_HEIGHT_SIZE; y++)
    {
        SetConsolePointer({ 0, y });
        printf(renderBuffer[y]);
    }

    ClearBuffer();
    return true;
}


void SetConsolePointer(uvector2 position)
{
    COORD cur;
    cur.X = position.x;
    cur.Y = position.y;
    SetConsoleCursorPosition(cursorPointerHandler, cur);
}

bool NullTermimation()
{
    for (int y = 0; y < RENDER_BUFFER_HEIGHT_SIZE; y++)
    {
        renderBuffer[y][RENDER_BUFFER_WIDTH_SIZE- 1] = '\0';
    }

    return false;
}


