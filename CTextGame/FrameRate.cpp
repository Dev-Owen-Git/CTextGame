#include "FrameRate.h"

#include <Windows.h>

LARGE_INTEGER _freq, _currTime, _prevTime;

int _fps;
int _fpsMS;
float _deltaTime, _elapsedTime;

void InitFrameRate(const int fps)
{
    _fps = fps;
    _fpsMS = 1 / _fps ;

    QueryPerformanceFrequency(&_freq);
    QueryPerformanceCounter(&_currTime);
    QueryPerformanceCounter(&_prevTime);
}

bool CheckForFrame() 
{
    if (_elapsedTime >= _fpsMS)
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

void WaitforFrame()
{
    QueryPerformanceCounter(&_currTime);

    // TODO a 변수명 변경
    auto a = (_currTime.QuadPart - _prevTime.QuadPart);
    auto deltaTime = a / (float)_freq.QuadPart;

    _currTime.QuadPart -= (deltaTime - _fpsMS) * (float)_freq.QuadPart;

    _prevTime = _currTime;

    Sleep((_currTime.QuadPart / (float)_freq.QuadPart));
}
