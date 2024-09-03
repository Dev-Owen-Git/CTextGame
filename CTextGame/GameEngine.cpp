#include "GameEngine.h"

#include "Stage.h"
#include <Windows.h>
#include "Renderer.h"
#include "FrameRate.h"
#include<time.h>

#include <stdio.h>

void SetWindow(const int wdith, const int hegiht)
{
    char windowSizeBuffer[256] = "mode con: cols=%d lines=%d";
    sprintf_s(windowSizeBuffer, windowSizeBuffer, wdith  + 1, hegiht  + 1);
    system(windowSizeBuffer);
}

bool GameEngineInit()
{
    srand((unsigned int)time(NULL));

    SetWindow(RENDER_BUFFER_WIDTH_SIZE, RENDER_BUFFER_HEIGHT_SIZE);

    InitFrameRate(50);

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
