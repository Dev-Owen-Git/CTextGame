#include "FrameRate.h"

#include <Renderer/Renderer.h>

#include <Windows.h>
#pragma comment(lib, "Winmm.lib")


double FixedDeltaTime;

unsigned int _fps, _fpsToSeconds;

unsigned short _currentFrameCount = 0, _currentRenderCount = 0, _skipCount = 0;
unsigned short _prevFrameCount = 0, _prevRenderCount = 0, _prevSkipCount = 0;

int _currentFrameTime, _startFrameTime, _frameSkipCount = 0;

void InitFrameRate(const unsigned int fps)
{
    _fps = fps;
    _fpsToSeconds = 1000 / _fps;
    FixedDeltaTime = 1.0f / _fps;

    _currentFrameTime = timeGetTime();
    _startFrameTime = timeGetTime();

    timeBeginPeriod(1);
}

bool FrameSkip()
{
    return _frameSkipCount > 0;
}

void WaitforFrame()
{
    _currentFrameTime = timeGetTime();

    unsigned int processTime = _currentFrameTime - _startFrameTime;

    if (_fpsToSeconds >= processTime)
    {
        _skipCount++;
        Sleep(_fpsToSeconds - processTime);
    }
    
    if (processTime >= 1)
    {
        _frameSkipCount = (processTime / _fpsToSeconds) - 1;
    }

    _startFrameTime += _fpsToSeconds;
}



int FrameProcess()
{
    _currentFrameCount++;

    static unsigned int frameRenderTime = timeGetTime();

    if (timeGetTime() - frameRenderTime >= 1000)
    {
        // frame count
        _prevFrameCount = _currentFrameCount;
        _currentFrameCount = 0;
        
        // skip count
        _prevSkipCount = _skipCount;
        _skipCount = 0;

        // render count
        _prevRenderCount = _currentRenderCount;
        _currentRenderCount = 0;

        frameRenderTime += 1000;
    }
    return 0;
}

int FrameRender()
{
    _currentRenderCount++;

    static char logicFrameBuffer[MAXWORD] = "logic fps : ";
    static char renderFrameBuffer[MAXWORD] = "render fps : ";
    static char skipCountBuffer[MAXWORD] = "skip count : ";

    _itoa_s(_prevFrameCount, &logicFrameBuffer[12], MAXWORD - 12, 10);
    _itoa_s(_prevRenderCount, &renderFrameBuffer[13], MAXWORD - 13, 10);
    _itoa_s(_prevSkipCount, &skipCountBuffer[13], MAXWORD - 13, 10);

    CopyDataToRendBuffer({ 45, 0 }, logicFrameBuffer);
    CopyDataToRendBuffer({ 45, 1 }, renderFrameBuffer);
    CopyDataToRendBuffer({ 45, 2 }, skipCountBuffer);
    return 0;
}