#include "FrameRate.h"

#include "Renderer.h"
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")


unsigned int _fps, _fpsToSeconds;

unsigned short _currentFrameCount = 0, _currentRenderCount = 0;
unsigned short _prevFrameCount = 0, _prevRenderCount = 0;

int _currentFrameTime, _startFrameTime, _frameSkipCount = 0;

void InitFrameRate(const unsigned int fps)
{
    _fps = fps;
    _fpsToSeconds = 1000 / _fps;

    timeBeginPeriod(1);

    _currentFrameTime = timeGetTime();
    _startFrameTime = timeGetTime();
}

bool FrameSkip()
{
    return _frameSkipCount > 0;
}

void WaitforFrame()
{
    _currentFrameTime = timeGetTime();

    auto processTime = _currentFrameTime - _startFrameTime;

    if (_fpsToSeconds >= processTime)
    {
        Sleep(_fpsToSeconds - processTime);
    }
    
    if (processTime >= (_fpsToSeconds << 1))
    {
        _frameSkipCount = (processTime / _fpsToSeconds) - 1;
    }
    else
    {
        _frameSkipCount = 0;
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

        frameRenderTime += 1000;
    }
    return 0;
}

int RenderFrame()
{
    _currentRenderCount++;

    static unsigned int frameRenderTime = timeGetTime();

    if (timeGetTime() - frameRenderTime >= 1000)
    {
        _prevRenderCount = _currentRenderCount;
        _currentRenderCount = 0;

        frameRenderTime += 1000;
    }

    static char logicFrameBuffer[MAXWORD];
    static char renderFrameBuffer[MAXWORD];
    _itoa_s(_prevFrameCount, logicFrameBuffer, 10);
    _itoa_s(_prevRenderCount, renderFrameBuffer, 10);

    CopyDataToRendBuffer({ 45, 0 }, logicFrameBuffer);
    CopyDataToRendBuffer({ 45, 2 }, renderFrameBuffer);
    return 0;
}