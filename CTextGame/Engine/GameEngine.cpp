#include "GameEngine.h"

#include <Stage/Stage.h>
#include <Renderer/Renderer.h>
#include <FrameRate/FrameRate.h>
#include <Data/GlobalData.h>

#include <ctime>
#include <cstdio>
#include <Windows.h>

static const int DEFAULT_FPS = 50;

void SetWindow(const int wdith, const int hegiht)
{   
    char windowSizeBuffer[256] = "mode con: cols=%d lines=%d";
    sprintf_s(windowSizeBuffer, windowSizeBuffer, wdith  + 10, hegiht  + 10);
    system(windowSizeBuffer);
}

bool GameEngineInit()
{
    srand((unsigned int)time(NULL));

    // consle window size
    SetWindow(RENDER_BUFFER_WIDTH_SIZE, RENDER_BUFFER_HEIGHT_SIZE);

    // frame
    InitFrameRate(DEFAULT_FPS);

    if (StageInit() == false)
    {
        return false;
    }
    if (RendererInit() == false)
    {
        return false;
    }

    return SetStage(StageType::Title);
}

int GameEngineStart()
{
    while (true)
    {
        // logic fps check
#ifdef _DEBUG
        FrameProcess();
#endif

        // frame Test
        if (GetAsyncKeyState(VK_F1))
        {
            Sleep(150);
        }

        // Process
        StageInput();
        StageProcess();

        if (FrameSkip() == false)
        {
#ifdef _DEBUG
            // render fps check 
            FrameRender();
#endif
            
            // stage render
            StageRender();

            // BUFFER ±×¸®±â
            DrawBuffer();
        }

        // Wait
        WaitforFrame();
    }

    return 0;
}
