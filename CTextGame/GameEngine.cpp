#include "GameEngine.h"

#include "Stage.h"
#include <Windows.h>
#include "Renderer.h"
#include "FrameRate.h"

bool GameEngineInit()
{
    InitFrameRate(50);

    StageInit();
    RendererInit();

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
