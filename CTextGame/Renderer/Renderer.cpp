#include "Renderer.h"

#include <Data/GlobalData.h>

#include <windows.h>
#include <cstdio>

char _renderBuffer[RENDER_BUFFER_HEIGHT_SIZE + 1][RENDER_BUFFER_WIDTH_SIZE + 1] = { ' ',};

HANDLE _cursorPointerHandler;

bool RendererInit()
{
    CONSOLE_CURSOR_INFO cursorInfo;

    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;

    _cursorPointerHandler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(_cursorPointerHandler, &cursorInfo);

    ClearBuffer();

    return true;
}

bool ClearBuffer()
{
    ::memset(_renderBuffer, ' ', sizeof(_renderBuffer));
    return true;
}

bool CopyDataToRendBuffer(const vector2D<unsigned int> position, const char render)
{
    _renderBuffer[position.y][position.x] = render;
    return true;
}

bool CopyDataToRendBuffer(const vector2D<unsigned int> position, const char* render)
{
    const int copySize = (const int)strlen(render);
    const int remingSize = RENDER_BUFFER_WIDTH_SIZE - copySize;
    ::memcpy_s(&_renderBuffer[position.y][position.x], remingSize, (const void*) render, copySize);
    return true;
}

bool DrawBuffer()
{
    NullTermimation();

    for (unsigned short y = 0; y < RENDER_BUFFER_HEIGHT_SIZE + 1; y++)
    {
        SetConsolePointer({ 0, y });
        printf(_renderBuffer[y]);
    }

    ClearBuffer();
    return true;
}


void SetConsolePointer(vector2D<unsigned short> position)
{
    COORD cur;
    cur.X = position.x;
    cur.Y = position.y;
    SetConsoleCursorPosition(_cursorPointerHandler, cur);
}

bool NullTermimation()
{
    for (int y = 0; y < RENDER_BUFFER_HEIGHT_SIZE; y++)
    {
        _renderBuffer[y][RENDER_BUFFER_WIDTH_SIZE] = '\n';
    }

    return false;
}


