#include "FrameRate.h"

#include <Windows.h>

LARGE_INTEGER _freq, _currTime, _prevTime;

int _fps;
float _deltaTime, _elapsedTime;

void InitFrameRate(const int fps)
{
    _fps = fps;

    QueryPerformanceFrequency(&_freq);
    QueryPerformanceCounter(&_currTime);
    QueryPerformanceCounter(&_prevTime);
}

bool CheckForFrame() 
{
    if (_elapsedTime >= 1.0f / _fps)
    {
        _elapsedTime = 0;
        return true;
    }

    return false;
}


void UpdateFrame()
{
    QueryPerformanceCounter(&_currTime);

    _elapsedTime += (_currTime.QuadPart - _prevTime.QuadPart) / (float)_freq.QuadPart;

    _prevTime = _currTime;
}
