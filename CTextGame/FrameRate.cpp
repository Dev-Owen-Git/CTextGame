#include "FrameRate.h"

#include "Renderer.h"

#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

LARGE_INTEGER _freq, _frameStartTime, _currentFrameTime;

unsigned int _fps;
float _fpsMS;

unsigned short _frameCount = 0;

void InitFrameRate(const unsigned int fps)
{
    _fps = fps;
    _fpsMS = 1.0f / _fps ;

    QueryPerformanceFrequency(&_freq);
    QueryPerformanceCounter(&_frameStartTime);
    QueryPerformanceCounter(&_currentFrameTime);

    timeBeginPeriod(1);
}

void WaitforFrame()
{
    QueryPerformanceCounter(&_currentFrameTime);
    auto processTime = (_currentFrameTime.QuadPart - _frameStartTime.QuadPart) / (float)_freq.QuadPart;

    if (_fpsMS >= processTime)
    {
        Sleep((_fpsMS - processTime) * 1000);
    }
    else
    {

    }

    _frameStartTime.QuadPart += _fpsMS * _freq.QuadPart;
}



int ProcessFrame()
{
    _frameCount++;
    return 0;
}

int RenderFrame()
{
    static unsigned int frameRenderTime = timeGetTime();
    
    if (timeGetTime() - frameRenderTime >= 1000)
    {
        printf("%d\n", _frameCount);
        _frameCount = 0;
        frameRenderTime = timeGetTime();
    }

    return 0;
}