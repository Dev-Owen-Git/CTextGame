#include "FrameRate.h"

#include "Renderer.h"
#include <stdlib.h>
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")


unsigned int _fps, _fpsToSeconds;

unsigned short _currentFrameCount = 0;
unsigned short _prevFrameCount = 0;

int _currentFrameTime, _startFrameTime;

void InitFrameRate(const unsigned int fps)
{
    _fps = fps;
    _fpsToSeconds = 1000 / _fps;

    timeBeginPeriod(1);

    _currentFrameTime = timeGetTime();
    _startFrameTime = timeGetTime();
}

void WaitforFrame()
{
    _currentFrameTime = timeGetTime();

    auto processTime = _currentFrameTime - _startFrameTime;

    if (_fpsToSeconds >= processTime)
    {
        Sleep(_fpsToSeconds - processTime);
    }

    _startFrameTime += _fpsToSeconds;
}



int ProcessFrame()
{
    _currentFrameCount++;

    static unsigned int frameRenderTime = timeGetTime();

    if (timeGetTime() - frameRenderTime >= 1000)
    {
        _prevFrameCount = _currentFrameCount;
        _currentFrameCount = 0;
        frameRenderTime = timeGetTime();
    }
    return 0;
}

int RenderFrame()
{
    static char buffer[sizeof(_prevFrameCount) + 1];
    _itoa_s(_prevFrameCount, buffer, 10);

    CopyDataToRendBuffer({ 45, 0 }, buffer);
    return 0;
}
